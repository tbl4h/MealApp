#pragma once
#include "../headers/meals_list.h"

namespace MealsList
{
    struct MealsList::Impl
    {
        std::unordered_map<std::string, MealData> _MealsList;
        sqlite3 *_Db = nullptr;
        char *_ZErrMsg = nullptr;
        int _Rc = 0;
        std::string _Sql;
    };

    MealsList::~MealsList()
    {
        sqlite3_close(_impl->_Db);
        /*
        if(_impl->_ZErrMsg != nullptr)
            std::free(_impl->_ZErrMsg);
            */
    };
    int MealsList::my_special_callback(void *unused, int count, char **data, char **columns)
    {
        

        printf("There are %d column(s)\n", count);

        for (int idx = 0; idx < count; idx++)
        {
            printf("The data in column \"%s\" is: %s\n", columns[idx], data[idx]);
        }

        printf("\n");

        return 0;
    };
    MealsList::MealsList()
    {
        _impl = std::make_unique<Impl>();
        _impl->_Rc = sqlite3_open("./MealsList.db", &_impl->_Db);
        if (_impl->_Rc)
        {
            std::cerr << "Can't open database: MealsList.db\n";
        }
        else
        {
            std::cerr << "Opened database successfully\n";
        }
        _impl->_Sql = "CREATE TABLE MEALS("
                      "NAME           TEXT   PRIMARY KEY  NOT NULL,"
                      "INGREDIENTS    TEXT,"
                      "PREPARATION_TIME     INT,"
                      "COOKING_TIME   INT,"
                      "DIFFICULTY     TEXT,"
                      "PORTIONS       INT,"
                      "KCAL           INT,"
                      "FAT            INT,"
                      "CARBS          INT,"
                      "PROTEIN        INT,"
                      "STEPS          TEXT);";
        /* Execute SQL statement */
        _impl->_Rc = sqlite3_exec(_impl->_Db, _impl->_Sql.c_str(), MealsList::my_special_callback, NULL, &_impl->_ZErrMsg);

        if (_impl->_Rc != SQLITE_OK)
        {
            std::cerr << "Table can't be created.\n"
                      << _impl->_ZErrMsg << std::endl;
            sqlite3_free(_impl->_ZErrMsg);
        }
        else
        {
            std::cerr << "Table created successfully\n";
        }
        _impl->_Sql = "";
        std::cout << "Create Meals list." << std::endl;
    };
    void MealsList::addMeal(const std::string &meal)
    {
        MealData tmp;
        auto isInData = _impl->_MealsList.find(meal);
        if (isInData == _impl->_MealsList.end())
        {
            _impl->_MealsList.insert(std::make_pair(meal, tmp));
        }
        else
        {
            std::cout << "Meal is actually in meals list." << std::endl;
        }
    }
    int MealsList::dataSize() const
    {
        return _impl->_MealsList.size();
    }
    bool MealsList::findMeal(const std::string &mealName)
    {
        auto isInData = _impl->_MealsList.find(mealName);
        if (isInData == _impl->_MealsList.end())
        {
            return false;
        }
        else
        {
            return true;
        }
    }
    void MealsList::addMealsList(std::unordered_map<std::string, MealData> tmpMealsList)
    {
        for (auto tmpMeal : tmpMealsList)
        {
            auto isMealInTheList = _impl->_MealsList.find(tmpMeal.first);
            if (isMealInTheList == _impl->_MealsList.end())
            {
                _impl->_MealsList.insert(tmpMeal);
            }
            else
            {
                continue;
            }
        }
    }
    void MealsList::addMealsToDatabase()
    {
        for (auto Meal : _impl->_MealsList)
        {

            std::stringstream my_stream;
            my_stream << "INSERT OR IGNORE INTO MEALS (`NAME`, `INGREDIENTS`, `PREPARATION_TIME`, `COOKING_TIME`, `DIFFICULTY`, `PORTIONS`, `KCAL`, `FAT`, `CARBS`, `PROTEIN`, `STEPS`) ";
            my_stream << "VALUES (";
            my_stream << "'";
            my_stream << Meal.first;
            my_stream << "'";
            my_stream << ", ";
            if (Meal.second.ingredients.empty())
            {
                my_stream << "'";                
                my_stream << "'";
            }
            for (auto Ingredient : Meal.second.ingredients)
            {
                my_stream << "'";
                my_stream << Ingredient;
                my_stream << "'";
            }
            my_stream << ", ";
            my_stream << Meal.second.prepTime;
            my_stream << ", ";
            my_stream << Meal.second.cookTime;
            my_stream << ", ";
            my_stream << "'";
            my_stream << Meal.second.difficulty;
            my_stream << "'";
            my_stream << ", ";
            my_stream << Meal.second.portions;
            my_stream << ", ";
            my_stream << Meal.second.kcal;
            my_stream << ", ";
            my_stream << Meal.second.fat;
            my_stream << ", ";
            my_stream << Meal.second.carbs;
            my_stream << ", ";
            my_stream << Meal.second.protein;
            my_stream << ", ";
            my_stream << "'";
            for (auto Steps : Meal.second.steps)
            {
                my_stream << Steps.first;
                my_stream << ": ";
                my_stream << Steps.second;
                // change it
                my_stream << "nn";
            }
            my_stream << "'";
            my_stream << " );";
            _impl->_Sql = my_stream.str();            
            _impl->_Rc = sqlite3_exec(_impl->_Db, _impl->_Sql.c_str(), MealsList::my_special_callback, NULL, &_impl->_ZErrMsg);

            if (_impl->_Rc != SQLITE_OK)
            {
                std::cerr << "Can't add values to database: \n"
                          << _impl->_ZErrMsg << std::endl;
                sqlite3_free(_impl->_ZErrMsg);
            }
            else
            {
                std::cerr << "Add value successfully.\n";
            }
        }
    }
}
