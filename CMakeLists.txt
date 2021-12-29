cmake_minimum_required(VERSION 3.17)
project(timeseries)

set(CMAKE_CXX_STANDARD 14)


include_directories(.)

#add_executable(timeseries
#        anomaly_detection_util.cpp
#        anomaly_detection_util.h
#        minCircle.cpp
#        minCircle.h
#        CircleTest.cpp)

add_executable(timeseries
        anomaly_detection_util.cpp
        anomaly_detection_util.h
        minCircle.cpp
        minCircle.h
        timeseries.cpp
        timeseries.h
        SimpleAnomalyDetector.cpp
        SimpleAnomalyDetector.h
        HybridAnomalyDetector.cpp
        HybridAnomalyDetector.h
        commands.h
        CLI.cpp
        CLI.h
        MainTrain.cpp)
