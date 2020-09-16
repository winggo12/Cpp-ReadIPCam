cmake_minimum_required(VERSION 3.0 FATAL_ERROR)
project(Cam)

find_package( OpenCV REQUIRED )
include_directories("/home/luisrman/opencv-3.4.6")

set(SOURCES main.cpp)

add_executable(Cam ${SOURCES})
	
target_link_libraries(Cam ${OpenCV_LIBS} libpthread.so.0)
set_property(TARGET Cam PROPERTY CXX_STANDARD 14)
