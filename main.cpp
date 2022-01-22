#include "./headers/meal.h"
#include "./headers/rolling_function.h"
#include "./headers/meals_list.h"
#include "./headers/parse_meal.h"

int main(int argc, char *argv[]) {
    MealParser::MealParser myParser;
    MealsList::MealsList myList;
    myParser.getDataFromRange(1,4);
    myList.addMealsList(myParser.getCacheData());
    myList.addMealsToDatabase();
    myList.displayList();
    
}