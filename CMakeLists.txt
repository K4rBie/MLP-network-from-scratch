cmake_minimum_required(VERSION 3.5)

project(MLP-network-example LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(MLP-network-example
    main.cpp
    layers.cpp
    layers.h
    matrix.cpp
    matrix.h
    model.cpp
    model.h
    modeldefinition.h
    )
