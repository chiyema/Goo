cmake_minimum_required(VERSION 3.6)
project(Goo)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES
    AppDelegate.h
    AppDelegate.mm
    BASE.h
    BRIDGE.h
    "four element type.h"
    "grammar scanner.h"
    main.m
    MORPHOLOGY.h
    "target code.h"
    ViewController.h
    ViewController.mm)

add_executable(Goo ${SOURCE_FILES})