cmake_minimum_required(VERSION 3.16)
project(StoOpt)

set(CMAKE_CXX_STANDARD 14)

add_executable(StoOpt main.cpp utils/FileUtil.h utils/FileUtil.cpp)
