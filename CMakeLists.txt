cmake_minimum_required(VERSION 3.17)
project(timeseries)

set(CMAKE_CXX_STANDARD 14)

add_executable(timeseries testCSV.csv SimpleAnomalyDetector.cpp SimpleAnomalyDetector.h anomaly_detection_util.cpp
        anomaly_detection_util.h timeseries.cpp timeseries.h MainTrain.cpp)