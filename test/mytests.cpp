#include <gtest/gtest.h>
#include "gmock/gmock.h"
#include "../headers/meal.h"
#include "../headers/rolling_function.h"

TEST(Meal_class, Meal_class_constructor)
{    
    Meal myMeal(Meals::Rice_and_chicken);
    EXPECT_THAT(myMeal.get_name(),"Rice and chicken");    
}
TEST(Meal_class, Meal_class_constructor_argument_is_out_of_range){
    EXPECT_THROW(Meal _meal(static_cast<Meals>(10)),std::out_of_range); 
}
TEST(Rolling_function, roll_in_Meals_range)
{    
    for(int i=0;i<100;i++){
        Meals meal = roll();    
        EXPECT_NO_THROW(Meal _meal(meal));
    }
      
}
int main(int argc, char* argv[])
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}