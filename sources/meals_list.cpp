#pragma once 
#include "../headers/meals_list.h"

namespace MealsList{
    struct MealsList::Impl {
        std::vector<std::string> _MealsList;
        // const H5std_string FILE_NAME("SDS_Meal.h5");
    };
    
    MealsList::~MealsList() = default;
    MealsList::MealsList(): _impl(new Impl){
        _impl->_MealsList.push_back("Spagetti");
        _impl->_MealsList.push_back("Pizza");
        _impl->_MealsList.push_back("Fish and Chips");
        _impl->_MealsList.push_back("Rice and chicken");
        _impl->_MealsList.push_back("Salmon");
        _impl->_MealsList.push_back("Roasted beef");
        _impl->_MealsList.push_back("Sushi"); 

    };
    void MealsList::addMeal(std::string meal) {
        _impl->_MealsList.push_back(meal);
    }
    int MealsList::dataSize() const {
        return _impl->_MealsList.size();
    }
}