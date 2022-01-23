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
#include "../headers/shared_structure.h"
#include "../headers/stack_checking_resource.h"

namespace MealParser
{    
    class MealParser
    {
    private:
        struct Impl;
        inline static constexpr std::size_t OverPageSize = 641224;
        inline static stack_checking_resource<OverPageSize> resource;
        inline static std::pmr::string my_str{&MealParser::resource};                
        std::unique_ptr<Impl> impl;
        /**
         * @brief initialized all sources required by CURLib
         * 
         * @return true if initailization is successful
         * @return false if initalization is failed
         */
        bool initCurl();
        /**
         * @brief function callback used to allocated sufficiency memory to download required webpage
         * 
         * @param contents 
         * @param size 
         * @param nmemb 
         * @param userp 
         * @return size_t size of allocated memory
         */
        static size_t WriteMemoryCallback(void *contents, size_t size, size_t nmemb, void *userp);
    public:
        /**
         * @brief Get the Webpage sources
         * 
         * @param number according to Website number by default is download from first  
         * @return true when download the content is successful
         * @return false when downladed the content is failed
         */
        bool [[nodiscard("Function returned value should be use.")]] getPage(int number = 1);
        /**
         * @brief Parse meals names from downladed webpage
         * 
         * @return true when parsed successful
         * @return false when parsed faild
         */
        bool parseMeals();
        /**
         * @brief Return GetSuccess flag witch is ones of the possible value contains in CURLcode enum
         * 
         * @return true when flag is CURL_OK
         * @return false when flag is other CURLcode value
         */
        bool isGetSuccess();
        /**
         * @brief Get the Data From Range of possible website pages
         * 
         * @param start is first webpage witch of starts to downloading
         * @param end is last webpage in downloading range
         * @return true if all arguments are in the possible range  
         * @return false when ones of the argument is out of the range
         */
        bool getDataFromRange(int start,int end);
        /**
         * @brief display downloaded data to standard output
         * 
         */
        void listCacheData();
        /**
         * @brief finds meal in the list 
         * 
         * @param meal_name contains searching name
         * @return true if meal pased to the function is on the meals list
         * @return false if there is no meal name  on the current list
         */
        bool findMealInCacheData(std::string meal_name);
        /**
         * @brief Get the Cache Data object witch is actually all meals parsed from the websites
         * 
         * @return std::unordered_map<std::string, MealData> of meals and its data  
         */
        std::unordered_map<std::string, MealData> getCacheData() const;
        /**
         * @brief Construct a new Meal Parser object
         * 
         */
        MealParser();
        /**
         * @brief Destroy the Meal Parser object
         * 
         */
        ~MealParser();
    };
}


/* TO DO */ 
/* Change as much as it possible to constexpression things */