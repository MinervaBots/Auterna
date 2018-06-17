cmake_minimum_required(VERSION 3.10)
project(Auterna)

set(CMAKE_CXX_STANDARD 11)

include_directories(.)
include_directories(Auterna)
include_directories(OpponentDetector)
include_directories(StarStrategy)
include_directories(StateMachine)

add_executable(Auterna
        Auterna/Auterna.cpp
        Auterna/Auterna.h
        OpponentDetector/OpponentDetector.cpp
        OpponentDetector/OpponentDetector.h
        StarStrategy/StarStrategy.cpp
        StarStrategy/StarStrategy.h
        StateMachine/StateMachine.h
        MotorControl.cpp
        MotorControl.hpp
        PidControl.cpp
        PidControl.h
        Sensors.h
        test.cpp main.cpp Sensors.cpp)
