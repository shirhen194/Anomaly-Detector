cmake_minimum_required(VERSION 3.17)
project(timeseries)

set(CMAKE_CXX_STANDARD 14)

add_executable(timeseries testCSV.csv timeseries.cpp timeseries.h main.cpp)