cmake_minimum_required(VERSION 3.17)
project(anomaly_detector)

set(CMAKE_CXX_STANDARD 14)

add_executable(anomaly_detector anomaly_detection_util.cpp anomaly_detection_util.h)