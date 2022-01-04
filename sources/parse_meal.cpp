#include "../headers/parse_meal.h"
#include "../headers/mpc.h"

namespace MealParser
{
    struct MealParser::MemoryStruct
    {
        char *memory = nullptr;
        size_t size = 0;
    };

    struct MealParser::MealData {
        std::vector<std::string> ingredients;
        int prepTime = 0;
        int cookTime = 0;
        std::string difficulty;
        int portions = 0;
        int kcal = 0;
        int fat = 0;
        int carbs = 0;
        int protein = 0;
        std::unordered_map<std::string,std::string> steps;
    };
    struct MealParser::Impl
    {
        std::unordered_map<std::string, MealParser::MealData>  _MealsCacheData;
        CURL *_Curl = nullptr;
        bool _CurlInit;
        CURLcode _Res;
        MealParser::MemoryStruct _Chunk;
        std::string downloadMemory;
        static constexpr char _Postthis[24] = "Field=1&Field=2&Field=3";
        static constexpr char _MainUrl[] = "https://www.bbcgoodfood.com/recipes/collection/family-meal-recipes?page=";
    };
    constexpr char MealParser::Impl::_Postthis[];
    constexpr char MealParser::Impl::_MainUrl[];
    bool MealParser::initCurl()
    {
        curl_global_init(CURL_GLOBAL_ALL);
        _impl->_Curl = curl_easy_init();
        if (_impl->_Curl == NULL)
            throw std::runtime_error("libCurl faild to initialize.\n");
        curl_easy_setopt(_impl->_Curl, CURLOPT_WRITEFUNCTION, MealParser::WriteMemoryCallback);
        curl_easy_setopt(_impl->_Curl, CURLOPT_WRITEDATA, (void *)&_impl->_Chunk);
        curl_easy_setopt(_impl->_Curl, CURLOPT_USERAGENT, "libcurl-agent/1.0");
        curl_easy_setopt(_impl->_Curl, CURLOPT_POSTFIELDS, _impl->_Postthis);
        curl_easy_setopt(_impl->_Curl, CURLOPT_POSTFIELDSIZE, (long)strlen(_impl->_Postthis));
        return true;
    };
    MealParser::MealParser() : _impl(new Impl)
    {
        _impl->_CurlInit = initCurl();
    }
    MealParser::~MealParser()
    {
        curl_easy_cleanup(_impl->_Curl);
        free(_impl->_Chunk.memory);
        curl_global_cleanup();
    };
    size_t MealParser::WriteMemoryCallback(void *contents, size_t size, size_t nmemb, void *userp)
    {
        size_t realsize = size * nmemb;

        MemoryStruct *mem = (MemoryStruct *)userp;

        char *ptr = (char *)std::realloc(mem->memory, mem->size + realsize + 1);
        if (!ptr)
        {
            /* out of memory! */
            std::cout << ("Not enough memory (realloc returned NULL)\n");
            return 0;
        }

        mem->memory = ptr;
        std::memcpy(&(mem->memory[mem->size]), contents, realsize);
        mem->size += realsize;
        mem->memory[mem->size] = 0;

        return realsize;
    }

    bool MealParser::getPage(int number)
    {
        std::string string_number = std::to_string(number);
        std::string MainURL = _impl->_MainUrl;

        MainURL.append(string_number);
        curl_easy_setopt(_impl->_Curl, CURLOPT_URL, MainURL.c_str());
        _impl->_Res = curl_easy_perform(_impl->_Curl);
        if (_impl->_Res != CURLE_OK)
        {
            throw std::runtime_error("curl_easy_perform() failed.\n");
        }
        else
        {
            _impl->downloadMemory = _impl->_Chunk.memory;
            const auto header1OpenTag = _impl->downloadMemory.find("<h1>");
            const auto header1CloseTag = _impl->downloadMemory.find("</h1>");
            std::string serviceUnavailableError = _impl->downloadMemory.substr(header1OpenTag + 4, header1CloseTag - (header1OpenTag + 4));
            if (serviceUnavailableError == "Error 503 first byte timeout.\n")
            {
                std::cout << "Error 503.\n";
                return false;
            }
            return true;
        }
    }

    bool MealParser::parseMeals()
    {

        std::string mealName;
        std::string terminationMeal("Magazine Subscription");
        std::string unorderedListElementOpen("<ul class=\"dynamic-list__list list\">");
        std::string unorderedListElementClose("</ul>");
        std::string headerMealNameElement("<h2 class=\"d-inline heading-4\" style=\"color:inherit\">");

        const auto unorderedListStart = _impl->downloadMemory.find(unorderedListElementOpen);
        const auto unorderedListEnd = _impl->downloadMemory.find(unorderedListElementClose);
        std::string mealList = _impl->downloadMemory.substr(unorderedListStart, unorderedListEnd - (unorderedListStart + unorderedListElementOpen.size()));
        auto headerMealDelimiter = mealList.find(headerMealNameElement);
        auto headerMealDelimiterEnd = mealList.find("</h2>");
        MealParser::MealData tmp;
        do
        {
            headerMealDelimiter = mealList.find(headerMealNameElement);
            headerMealDelimiterEnd = mealList.find("</h2>");
            mealName = mealList.substr(headerMealDelimiter + headerMealNameElement.size(), headerMealDelimiterEnd - (headerMealDelimiter + headerMealNameElement.size()));
            if (mealName == terminationMeal)
                break;
            _impl->_MealsCacheData.insert(std::make_pair(mealName,tmp));
            mealList = mealList.substr(headerMealDelimiterEnd + 5);
        } while (mealName != terminationMeal);

        return true;
    };
    bool MealParser::isGetSuccess()
    {
        return _impl->_Res == CURLE_OK ? true : false;
    };
    void MealParser::listCacheData()
    {
        if (_impl->_MealsCacheData.size() == 0)
        {
            std::cout << "Nothing to list." << std::endl;
        }
        else
            for (auto meal : _impl->_MealsCacheData)
                std::cout << meal.first << std::endl;
    };
    bool MealParser::getDataFromRange(int start, int end)
    {
        bool isInRangeStart = getPage(start);
        bool isInRangeEnd = getPage(end);

        if (!isInRangeStart || !isInRangeEnd)
        {
            std::cout << "Passed argument is  out of possible range." << std::endl;
            return false;
        }
        else
        {
            for (int i = start; i <= end; i++){
                getPage(i);
                parseMeals();
            }
            return true;
        }
    }
    bool MealParser::findMealInCacheData(std::string meal_name){
        auto isInData = _impl->_MealsCacheData.find(meal_name);
        if(isInData != _impl->_MealsCacheData.end()){
            std::cout << meal_name << " is found in the cache data." << std::endl;
            return true;
        }else {
            std::cout << "There no " << meal_name << " in data." << std::endl;
            return false;
        }
    }
}
