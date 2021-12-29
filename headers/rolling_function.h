#pragma once
#include "meal.h"
#include <iostream>
#include <string>
#include <random>


std::random_device r;
std::default_random_engine e1(r());
std::uniform_int_distribution<int> uniform_dist(0, 6);

Meals roll(){
    int mean = uniform_dist(e1);
    Meals test = static_cast<Meals>(mean);
    return test;
}