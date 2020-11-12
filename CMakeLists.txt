cmake_minimum_required(VERSION 3.17)
project(SPL)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(SPL
        Agent.cpp
        Agent.h
        Graph.cpp
        Graph.h
        json.hpp
        main.cpp
        Session.cpp
        Session.h
        Tree.cpp
        Tree.h)
