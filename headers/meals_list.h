#pragma once
#include <vector>
#include <string>
#include <memory>
#include "gmock/gmock.h"
#include <H5Cpp.h>

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
    public:
        ~MealsList();
        MealsList();
        int dataSize()const override;
        void addMeal(std::string meal) override;
};
class MockMealsList : public MealsListInterface {
    public:
    MOCK_METHOD(int, dataSize, (), (const, override));
    MOCK_METHOD(void,addMeal,(std::string),(override));
};
}