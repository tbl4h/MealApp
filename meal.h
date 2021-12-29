#include <string.h>
#include <iostream>
#include <exception>
#pragma once
enum class Meals {Spagetti,Pizza,Fish_and_Chips,Rice_and_chicken,Salmon,Roasted_beef,Sushi};

class Meal {
    public:
    Meal(Meals meal);
    std::string get_name() const;
    ~Meal();
    private:
    std::string name; 
    Meal();   
};