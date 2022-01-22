#pragma once
#include <vector>
#include <string>
#include <memory>
#include "gmock/gmock.h"
#include "../headers/shared_structure.h"
#include <sqlite3.h>

namespace MealsList
{

    class MealsList {
    private:
        /**
         * @brief Contains all resources.
         * 
         */
        struct Impl;
        
        /**
         * @brief Ensure deallocate memory resources
         * 
         */
        std::unique_ptr<Impl> impl;
        
        /**
         * @brief Function used in libCurl while realize Get request 
         * 
         * @param unused 
         * @param count 
         * @param data 
         * @param columns 
         * @return int 
         */
        static int my_special_callback(void *unused, int count, char **data, char **columns);
        

    public:
        MealsList();
        ~MealsList();
        int dataSize() const;
        void addMeal(const std::string &meal);
        bool [[nodiscard("Consider to use return value.")]] findMeal(const std::string &mealName);
        void addMealsList(std::unordered_map<std::string, MealData> tmpMealsList);
        void addMealsToDatabase();
    };

}

/* TO DO */
/* Change some methods for lambda expressions. */