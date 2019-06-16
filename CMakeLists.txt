cmake_minimum_required(VERSION 3.14)
project(PasswordCracker)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_FLAGS -pthread)

include_directories(.)

add_executable(PasswordCracker
        Generator.cpp
        Generator.h
        main.cpp
        Queue.cpp
        Queue.h
        Validator.cpp
        Validator.h)
