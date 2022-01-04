#include "../headers/parse_meal.h"

namespace MealParser
{
    struct MealParser::MemoryStruct
    {
        char *memory = nullptr;
        size_t size = 0;
    };
    struct MealParser::Impl
    {
        std::vector<std::string> _MealsCacheData;
        CURL *_Curl = nullptr;
        bool _CurlInit;
        CURLcode _Res;
        MealParser::MemoryStruct _Chunk;
        std::string downloadMemory;
        static constexpr char _Postthis[24] = "Field=1&Field=2&Field=3";
        static constexpr char _MainUrl[] = "https://www.bbcgoodfood.com/recipes/collection/family-meal-recipes?page=1";
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
        curl_easy_setopt(_impl->_Curl, CURLOPT_URL, _impl->_MainUrl);
        _impl->_Res = curl_easy_perform(_impl->_Curl);
        if (_impl->_Res != CURLE_OK)
        {
            throw std::runtime_error("curl_easy_perform() failed.\n");
        }
        else
        {
            _impl->downloadMemory = _impl->_Chunk.memory;
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

        const auto header1OpenTag = _impl->downloadMemory.find("<h1>");
        const auto header1CloseTag = _impl->downloadMemory.find("</h1>");
        std::string serviceUnavailableError = _impl->downloadMemory.substr(header1OpenTag + 4, header1CloseTag - (header1OpenTag + 4));
        if (serviceUnavailableError == "Error 503 first byte timeout.\n")
        {
            std::cout << "Error 503.\n";
            return false;
        }
        else
        {
            const auto unorderedListStart = _impl->downloadMemory.find(unorderedListElementOpen);
            const auto unorderedListEnd = _impl->downloadMemory.find(unorderedListElementClose);
            std::string mealList = _impl->downloadMemory.substr(unorderedListStart, unorderedListEnd - (unorderedListStart + unorderedListElementOpen.size()));
            auto headerMealDelimiter = mealList.find(headerMealNameElement);
            auto headerMealDelimiterEnd = mealList.find("</h2>");
            do
            {
                headerMealDelimiter = mealList.find(headerMealNameElement);
                headerMealDelimiterEnd = mealList.find("</h2>");
                mealName = mealList.substr(headerMealDelimiter + headerMealNameElement.size(), headerMealDelimiterEnd - (headerMealDelimiter + headerMealNameElement.size()));
                if (mealName == terminationMeal)
                    break;
                _impl->_MealsCacheData.push_back(mealName);                
                mealList = mealList.substr(headerMealDelimiterEnd + 5);
            } while (mealName != terminationMeal);

            return true;
        }
    };
    bool MealParser::isGetSuccess()
    {
        return _impl->_Res == CURLE_OK ? true : false;
    };
}
