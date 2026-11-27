cmake_minimum_required(VERSION 3.16)


set(CMAKE_C_COMPILER /opt/loongson-gnu-toolchain-8.3-x86_64-loongarch64-linux-gnu-rc1.3-1/bin/loongarch64-linux-gnu-gcc)
set(CMAKE_CXX_COMPILER /opt/loongson-gnu-toolchain-8.3-x86_64-loongarch64-linux-gnu-rc1.3-1/bin/loongarch64-linux-gnu-g++)
set(CMAKE_FIND_ROOT_PATH/opt/loongson-gnu-toolchain-8.3-x86_64-loongarch64-linux-gnu-rc1.3-1/loongarch64-linux-gnu/sysroot/)
project(main)

file(GLOB SRC ${PROJECT_SOURCE_DIR}/src/*.c*)
include_directories(${PROJECT_SOURCE_DIR}/include)
include_directories(/opt/loongson-gnu-toolchain-8.3-x86_64-loongarch64-linux-gnu-rc1.3-1/loongarch64-linux-gnu/sysroot/usr/include/)

include_directories(/usr/local/include/opencv4/)
find_library(OPENCV_CORE           opencv_core           /usr/local/lib/)
find_library(OPENCV_IMGPROC        opencv_imgproc        /usr/local/lib/)
find_library(OPENCV_HIGHGUI        opencv_highgui        /usr/local/lib/)
find_library(OPENCV_VIDEOIO        opencv_videoio        /usr/local/lib/)
find_library(OPENCV_IMGCODECS      opencv_imgcodecs      /usr/local/lib/)




add_executable(main ${SRC})

target_link_libraries(main PUBLIC ${OPENCV_CORE} ${OPENCV_IMGPROC} ${OPENCV_HIGHGUI} ${OPENCV_VIDEOIO} ${OPENCV_IMGCODECS})

target_link_libraries(main PUBLIC rt pthread)
