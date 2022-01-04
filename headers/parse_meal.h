#pragma once
#include <curl/curl.h>
#include <string>
#include <vector>
#include <memory>
#include <system_error>
#include <new>
#include <stdio.h>
#include <stdlib.h>
#include <cstring>
#include <iostream>
#include <iostream>
#include <iomanip>
#include <memory>
#include <unordered_map>
namespace MealParser
{    
    class MealParser
    {
    private:
        struct Impl;        
        struct MealData;
        struct MemoryStruct;
        std::unique_ptr<Impl> _impl;
        
        bool initCurl();
        static size_t WriteMemoryCallback(void *contents, size_t size, size_t nmemb, void *userp);
    public:
        bool getPage(int number = 1);
        bool parseMeals();
        bool isGetSuccess();
        bool getDataFromRange(int start,int end);
        void listCacheData();
        bool findMealInCacheData(std::string meal_name);
        MealParser();
        ~MealParser();
    };
}