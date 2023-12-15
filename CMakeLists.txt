cmake_minimum_required(VERSION 3.14)
project(sshConnect)

include_directories(libs/json/include)


set(CMAKE_CXX_STANDARD 17)

add_executable(sshConnect
        User.cpp
        User.h
        sshConnect.cpp
)