#pragma once
#include <vector>
#include <string>
#include <memory>
#include "gmock/gmock.h"
#include "../headers/shared_structure.h"
#include <sqlite3.h> 

namespace MealsList{
class MealsListInterface{
    protected:
    virtual ~MealsListInterface(){};
    virtual int dataSize()const = 0;
    virtual void addMeal(std::string meal) = 0;
};
class MealsList : public MealsListInterface {
    private:
        struct Impl;
        std::unique_ptr<Impl> _impl;
        // methods
        static int my_special_callback(void *unused, int count, char **data, char **columns);
    public:
        ~MealsList();
        MealsList();
        int dataSize()const override;
        void addMeal(std::string meal) override;
        bool findMeal(std::string mealName);
        void addMealsList(std::unordered_map<std::string,MealData> tmpMealsList);
        void addMealsToDatabase();
};
class MockMealsList : public MealsListInterface {
    public:
    MOCK_METHOD(int, dataSize, (), (const, override));
    MOCK_METHOD(void,addMeal,(std::string),(override));
};
}