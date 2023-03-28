cmake_minimum_required(VERSION 3.15)
project(cv LANGUAGES CXX)
set(CMAKE_INCLUDE_CURRENT_DIR on)
set(CMAKE_CXX_STANDARD 17)
include_directories(inc)
include_directories(include)
link_directories(lib)
# set(CMAKE_LIBRARY_OUTPUT_DIRECTORY lib)
# set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY lib)
# set(CMAKE_RUNTIME_OUTPUT_DIRECTORY bin)

find_package(OpenCV REQUIRED)
include_directories(${OpenCV_INCLUDE_DIRS})
link_libraries(${OpenCV_LIBS})
MESSAGE("OpenCV version: ${OpenCV_VERSION}")
MESSAGE("OpenCV OpenCV_INCLUDE_DIRS: ${OpenCV_INCLUDE_DIRS}")
MESSAGE("OpenCV OpenCV_LIBS: ${OpenCV_LIBS}")

file(GLOB SRC "*.cc")

foreach(FILE ${SRC})
  get_filename_component(TARGET_NAME ${FILE} NAME_WE)
  add_executable(${TARGET_NAME} ${FILE})
endforeach()


