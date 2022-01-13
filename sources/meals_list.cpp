#include "../headers/meals_list.h"

namespace MealsList
{
    struct MealsList::Impl
    {
        std::unordered_map<std::string, MealData> MealsLIst;
        sqlite3 *Db = nullptr;
        char *ZErrMsg = nullptr;
        int Rc = 0;
        std::string Sql;
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
    }
    MealsList::~MealsList()
    {
        /* Free up space disk used in MealsList constructor - specially for all pointers occurring in impl structure */

        sqlite3_close(impl->Db);
        
        if(impl->ZErrMsg != nullptr)
            std::free(impl->ZErrMsg);
        
    }
    MealsList::MealsList()
    {
        impl = std::make_unique<Impl>();
        impl->Rc = sqlite3_open_v2("./MealsList.db", &impl->Db,SQLITE_OPEN_CREATE | SQLITE_OPEN_READWRITE,impl->ZErrMsg);
        if (impl->Rc)
        {
            std::cerr << "Can't open database: MealsList.db\n";
        }
        else
        {
            std::cerr << "Opened database successfully\n";
        }
        impl->Sql = "CREATE TABLE MEALS("
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
        impl->Rc = sqlite3_exec(impl->Db, impl->Sql.c_str(), MealsList::my_special_callback, NULL, &impl->ZErrMsg);

        if (impl->Rc != SQLITE_OK)
        {
            std::cerr << "Table can't be created.\n"
                      << impl->ZErrMsg << std::endl;
            sqlite3_free(impl->ZErrMsg);
        }
        else
        {
            std::cerr << "Table created successfully\n";
        }
        impl->Sql = "";
        std::cout << "Create Meals list." << std::endl;
    }
    void MealsList::addMeal(const std::string &meal)
    {
        MealData tmp;
        auto isInData = impl->MealsLIst.find(meal);
        if (isInData == impl->MealsLIst.end())
        {
            impl->MealsLIst.insert(std::make_pair(meal, tmp));
        }
        else
        {
            std::cout << "Meal is actually in meals list." << std::endl;
        }
    }
    int MealsList::dataSize() const
    {
        return impl->MealsLIst.size();
    }
    bool [[nodiscard ("Consider to use return value.")]] MealsList::findMeal(const std::string &mealName)
    {
        auto isInData = impl->MealsLIst.find(mealName);
        if (isInData == impl->MealsLIst.end())
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
            auto isMealInTheList = impl->MealsLIst.find(tmpMeal.first);
            if (isMealInTheList == impl->MealsLIst.end())
            {
                impl->MealsLIst.insert(tmpMeal);
            }
            else
            {
                continue;
            }
        }
    }
    void MealsList::addMealsToDatabase()
    {
        for (auto Meal : impl->MealsLIst)
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
            impl->Sql = my_stream.str();            
            impl->Rc = sqlite3_exec(impl->Db, impl->Sql.c_str(), MealsList::my_special_callback, NULL, &impl->ZErrMsg);

            if (impl->Rc != SQLITE_OK)
            {
                std::cerr << "Can't add values to database: \n"
                          << impl->ZErrMsg << std::endl;
                sqlite3_free(impl->ZErrMsg);
            }
            else
            {
                std::cerr << "Add value successfully.\n";
            }
        }
    }
}
