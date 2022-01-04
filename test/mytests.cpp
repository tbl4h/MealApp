#pragma once
#include <gtest/gtest.h>
#include "gmock/gmock.h"
#include "../headers/meal.h"
#include "../headers/rolling_function.h"

#include <memory>
#include "../headers/parse_meal.h"

TEST(Meal_class, constructor)
{
    Meal myMeal1(Meals::Spagetti);
    Meal myMeal2(Meals::Pizza);
    Meal myMeal3(Meals::Fish_and_Chips);
    Meal myMeal4(Meals::Rice_and_chicken);
    Meal myMeal5(Meals::Salmon);
    Meal myMeal6(Meals::Roasted_beef);
    Meal myMeal7(Meals::Sushi);
    EXPECT_THAT(myMeal1.get_name(), "Spagetti");
    EXPECT_THAT(myMeal2.get_name(), "Pizza");
    EXPECT_THAT(myMeal3.get_name(), "Fish and Chips");
    EXPECT_THAT(myMeal4.get_name(), "Rice and chicken");
    EXPECT_THAT(myMeal5.get_name(), "Salmon");
    EXPECT_THAT(myMeal6.get_name(), "Roasted beef");
    EXPECT_THAT(myMeal7.get_name(), "Sushi");
}
/*
TEST(MealClass, constructor_test){
    EXPECT_THROW(Meal _meal(static_cast<Meals>(10)),std::out_of_range);
}
*/
TEST(Rolling_function, rolling)
{
    for (int i = 0; i < 100; i++)
    {
        Meals meal = roll();
        EXPECT_NO_THROW(Meal _meal(meal));
    }
}
TEST(MealParser_class, get_page)
{
    MealParser::MealParser mealParser;
    mealParser.getPage();
    EXPECT_EQ(mealParser.isGetSuccess(), true);
}

TEST(MealParser_class, without_get_page)
{
    MealParser::MealParser mealParser;
    EXPECT_NE(mealParser.isGetSuccess(), true);
}
TEST(MealParser_class, parse_meals)
{
    MealParser::MealParser mealParser;
    mealParser.getPage();
    EXPECT_EQ(mealParser.parseMeals(), true);
}
/*
TEST(MealParser_class, list_cachedData)
{
    MealParser::MealParser mealParser;
    mealParser.getPage(1);
    mealParser.parseMeals();
    testing::internal::CaptureStdout();
    mealParser.listCacheData();
    std::string output = testing::internal::GetCapturedStdout();
    std::cout << "The captured output is: \n"
              << output << "\nEnd of capture.\n";

    EXPECT_EQ(output, "Easy chicken &amp; bean enchiladas\nCreamy chicken stew\nPrawn tikka masala\nPork &amp; apple burgers\nSausage &amp; leek mash pie\nChorizo &amp; mozzarella gnocchi bake\nPulled pork tacos with pineapple salsa\nPasta with salmon &amp; peas\nSausage &amp; mushroom ragu\nTeriyaki salmon &amp; green beans\nLemon &amp; greens pesto pasta\nCreamy courgette lasagne\nFajita-style pasta\nMeatball &amp; garlic bread traybake\n3-veg mac &#x27;n&#x27; cheese\nSlow-cooker chicken casserole\nSpiced koftas with honey &amp; chickpeas\nOne-pan egg &amp; veg brunch\nFish pie mac \xE2\x80\x99n\xE2\x80\x99 cheese\nCheesy ham hock, spinach &amp; ricotta lasagne\nSausage &amp; white bean casserole\nHow to roast a chicken\nPepper steak with noodles\nChicken pasta bake\n");
}
TEST(MealParser_class, getDataFromRange)
{
    MealParser::MealParser mealParser;    
    EXPECT_EQ(mealParser.getDataFromRange(1,10), true);
    mealParser.listCacheData();
}
*/
TEST(MealParser_class, findMealInCahceData){
    MealParser::MealParser mealParser;
    mealParser.getDataFromRange(1,1);
    EXPECT_EQ(mealParser.findMealInCacheData("Pasta with salmon &amp; peas"),true);

}
int main(int argc, char *argv[])
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}