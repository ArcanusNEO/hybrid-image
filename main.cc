#include "neocc.hh"

#include <opencv2/opencv.hpp>

#ifdef _CV_CUDA_

  #include <opencv2/cudaarithm.hpp>
  #include <opencv2/cudacodec.hpp>
  #include <opencv2/cudafeatures2d.hpp>
  #include <opencv2/cudaimgproc.hpp>
  #include <opencv2/cudawarping.hpp>

#endif  // _CV_CUDA_

using namespace cv;
using namespace std;

template <int type = 0>
Mat create_pfilter(Size size, float radius) {
  Mat filter = Mat::zeros(size, CV_32FC2);
  int row = size.height;
  int col = size.width;
  if (radius <= 0) {
    return filter;
  }
  for (int r = 0; r < row; ++r)
    for (int c = 0; c < col; ++c) {
      long long norm2 = square((long long) min(r, row - r)) +
        square((long long) min(c, col - c));
      filter.at<float>(r, c) =
        type + (1 - 2 * type) * exp(-norm2 / (2.0 * square(radius)));
    }
  return filter;
}

Mat create_lpfilter(Size size, float radius) {
  return create_pfilter<0>(size, radius);
}

Mat create_hpfilter(Size size, float radius) {
  return create_pfilter<1>(size, radius);
}

void dft_helper(InputArray src, OutputArray dst) {
  int m = getOptimalDFTSize(src.rows());
  int n = getOptimalDFTSize(src.cols());

  Mat padded;
  copyMakeBorder(src, padded, 0, m - src.rows(), 0, n - src.cols(),
    BORDER_DEFAULT, Scalar::all(0));

  Mat planes[] = {Mat_<float>(padded), Mat::zeros(padded.size(), CV_32F)};
  Mat complex_img;
  merge(planes, 2, complex_img);

  dft(complex_img, dst);
}

signed main(int argc, char* argv[]) {
  if (argc < 3) {
    cerr << "Usage: " << argv[0]
         << " image_path_1 image_path_2 [cutoff_frequency (default 20.0)]"
         << endl;
    exit(EXIT_FAILURE);
  }

  double radius = 20.0;
  if (argc >= 3) radius = max(atof(argv[3]), 0.0);

  Mat img_v[2] = {imread(argv[1], IMREAD_COLOR), imread(argv[2], IMREAD_COLOR)};

  if (img_v[0].empty() || img_v[1].empty()) {
    cerr << "Failed to read image" << endl;
    exit(EXIT_FAILURE);
  }

  if (img_v[0].size != img_v[1].size) {
    cerr << "Image size differ" << endl;
    exit(EXIT_FAILURE);
  }

  Mat freq_v_sc[2][3];

  Mat hybrid_freq_sc[3];

  for (int i = 0; i < 2; ++i) {
    Mat img_sc[3];
    split(img_v[i], img_sc);
    for (int j = 0; j < 3; ++j) dft_helper(img_sc[j], freq_v_sc[i][j]);
  }

  auto lpfilter = create_lpfilter(freq_v_sc[0][0].size(), radius);
  auto hpfilter = create_hpfilter(freq_v_sc[1][0].size(), radius);

  Mat hybrid_img_sc[3];

  for (int i = 0; i < 3; ++i) {
    // The real filter and hybrid step
    hybrid_freq_sc[i] =
      freq_v_sc[0][i].mul(lpfilter) + freq_v_sc[1][i].mul(hpfilter);

    idft(hybrid_freq_sc[i], hybrid_img_sc[i], DFT_SCALE | DFT_REAL_OUTPUT);

    hybrid_img_sc[i].convertTo(hybrid_img_sc[i], CV_8UC1);
    normalize(hybrid_img_sc[i], hybrid_img_sc[i], 0, 255, NORM_MINMAX);
  }

  Mat hybrid_img;
  merge(hybrid_img_sc, 3, hybrid_img);

  imshow("Hybrid Image", hybrid_img);

  return waitKey(0);
}
