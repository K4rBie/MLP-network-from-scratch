cmake_minimum_required(VERSION 3.5)
project(MLP-network-example LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(MLP-network-example
    main.cpp
    layers.cpp
    layers.h
    matrix.cpp
    matrix.h
    model.cpp
    model.h
    CImg.h
    )

# You can alter these according to your needs, e.g if you don't need to display images - set(YOU_NEED_X11 0)
set(YOU_NEED_X11 0)
set(YOU_NEED_PNG 0)
set(YOU_NEED_JPG 1)

if(${YOU_NEED_X11} EQUAL 1)
    message(STATUS "Looking for X11...")
    find_package(X11 REQUIRED)
    include_directories(${X11_INCLUDE_DIR})
    target_link_libraries(MLP-network-example ${X11_LIBRARIES})
else()
    target_compile_definitions(MLP-network-example PRIVATE cimg_display=0)
endif()

if(${YOU_NEED_JPG} EQUAL 1)
    message(STATUS "Looking for libjpg...")
    find_package(JPEG REQUIRED)
    include_directories(${JPEG_INCLUDE_DIR})
    target_link_libraries (MLP-network-example ${JPEG_LIBRARY})
    target_compile_definitions(MLP-network-example PRIVATE cimg_use_jpeg=1)
endif()

if(${YOU_NEED_PNG} EQUAL 1)
    message(STATUS "Looking for libpng...")
    find_package(PNG REQUIRED)
    include_directories(${PNG_INCLUDE_DIR})
    target_link_libraries (MLP-network-example ${PNG_LIBRARY})
    target_compile_definitions(MLP-network-example PRIVATE cimg_use_png=1)
endif()
