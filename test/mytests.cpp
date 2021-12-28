#include <gtest/gtest.h>
#include "../meal.h"
#include "../meals_list.h"

TEST(MealList, MealsList_name)
{
    std::string melasName[] = {"Pizza","Spagetti","Roasted Beef","Fish and Chips","Salmon","Rice and chicken","Sushi"};
    for(int i =0;i<7;i++){
        for(int j;j<7;j++){
            EXPECT_EQ(MealsList[i],melasName[j]);
        }
    }
}
TEST(MealList, MealsList_size)
{
    ASSERT_EQ(MealsList.size(),7);
}
int main(int argc, char* argv[])
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}