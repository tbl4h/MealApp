cmake_minimum_required(VERSION 3.8)
set(This MyTests)

set(Sources
    mytests.cpp
    ./../meal.cpp
)

add_executable(${This} ${Sources})

target_link_libraries(${This} PUBLIC
    gtest_main    
)

add_test(
    NAME ${This}
    COMMAND ${This}
)