# cmake_minimum_required (VERSION 2.6)

project (OpenCV_learn)

find_package( OpenCV REQUIRED )
FIND_PACKAGE(PkgConfig REQUIRED)

set(CMAKE_CXX_STANDARD 17)

include_directories(src)
file(GLOB SOURCES "src/*.h" "src/*.cpp" )
add_executable(OpenCV_learn ${SOURCES} OpenCV_learn.cpp)
target_link_libraries( OpenCV_learn ${OpenCV_LIBS})