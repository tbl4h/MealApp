#include <gtest/gtest.h>
#include "gmock/gmock.h"
#include "../meal.h"


TEST(Meal_class, Meal_class_constructor)
{    
    Meal myMeal(Meals::Rice_and_chicken);
    EXPECT_THAT(myMeal.get_name(),"Rice and chicken");    
}
int main(int argc, char* argv[])
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}