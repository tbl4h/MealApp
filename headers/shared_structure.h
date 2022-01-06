#pragma once
#include <unordered_map>
#include <string>
#include <vector>

struct MealData
{
    std::vector<std::string> ingredients;
    int prepTime = 0;
    int cookTime = 0;
    std::string difficulty;
    int portions = 0;
    int kcal = 0;
    int fat = 0;
    int carbs = 0;
    int protein = 0;
    std::unordered_map<std::string, std::string> steps;
};