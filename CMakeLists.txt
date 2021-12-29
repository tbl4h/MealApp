cmake_minimum_required(VERSION 3.8)
set(This MealApp)
project(${This} C CXX)
enable_testing()

add_subdirectory(googletest)
add_subdirectory(test)
file(GLOB_RECURSE fileCollection "./*.cpp")
set(Headers 
    ./headers/meal.h
    ./headers/rolling_function.h
    )
set(Sources 
    ./sources/meal.cpp
    ./sources/rolling_function.cpp
    )
add_library(${This} STATIC ${Sources} ${Headers})
