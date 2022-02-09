cmake_minimum_required(VERSION 3.16)
project(StoOpt)

set(CMAKE_CXX_STANDARD 14)
SET(CMAKE_C_FLAGS_DEBUG "-D_DEBUG")

add_executable(StoOpt src/main.cpp src/utils/FileUtil.h src/utils/FileUtil.cpp src/FAPSolver.cpp src/FAPSolver.h src/constructive/HEDGE.cpp src/constructive/HEDGE.h)
