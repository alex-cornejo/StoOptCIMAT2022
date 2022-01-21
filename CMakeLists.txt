cmake_minimum_required(VERSION 3.16)
project(StoOpt)

set(CMAKE_CXX_STANDARD 14)

add_executable(StoOpt src/main.cpp src/utils/FileUtil.h src/utils/FileUtil.cpp src/Solver.cpp src/Solver.h)
