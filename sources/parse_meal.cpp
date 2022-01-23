#include "../headers/parse_meal.h"
#include "../headers/mpc.h"

namespace MealParser
{

    struct MealParser::Impl
    {

        std::unordered_map<std::string, MealData> MealsCacheData;
        CURL *Curl = nullptr;
        bool CurlInit;
        CURLcode Res;
        std::string DownloadMemory;
        inline static constexpr std::string_view Postthis{"Field=1&Field=2&Field=3"};
        inline static constexpr std::string_view MainUrl{"https://www.bbcgoodfood.com/recipes/collection/family-meal-recipes?page="};
        inline static constexpr std::size_t PageSize = 541224;
    };


    bool MealParser::initCurl()
    {
        curl_global_init(CURL_GLOBAL_ALL);
        impl->Curl = curl_easy_init();
        if (impl->Curl == NULL)
            throw std::runtime_error("libCurl faild to initialize.\n");
        curl_easy_setopt(impl->Curl, CURLOPT_WRITEFUNCTION, MealParser::WriteMemoryCallback);
        // curl_easy_setopt(impl->Curl, CURLOPT_WRITEDATA, (void *)&impl->Chunk);
        curl_easy_setopt(impl->Curl, CURLOPT_USERAGENT, "libcurl-agent/1.0");
        curl_easy_setopt(impl->Curl, CURLOPT_POSTFIELDS, impl->Postthis.data());
        curl_easy_setopt(impl->Curl, CURLOPT_POSTFIELDSIZE, impl->Postthis.size());
        return true;
    }
    MealParser::MealParser()
    {
        impl = std::make_unique<Impl>();
        
        my_str.reserve(impl->PageSize);
        impl->CurlInit = initCurl();
    }
    MealParser::~MealParser()
    {
        curl_easy_cleanup(impl->Curl);
        curl_global_cleanup();
    }
    size_t MealParser::WriteMemoryCallback(void *contents, size_t size, size_t nmemb, void *userp)
    {
        size_t realsize = size * nmemb;
        // total += realsize;
        // std::cout << total << '\n';

        my_str.append(static_cast<char *>(contents), realsize);
        return realsize;
    }

    bool [[nodiscard("Function returned value should be use.")]] MealParser::getPage(int number)
    {
        std::string string_number = std::to_string(number);
        std::string MainURL(impl->MainUrl);
        MainURL.append(string_number);

        curl_easy_setopt(impl->Curl, CURLOPT_URL, MainURL.c_str());        
        impl->Res = curl_easy_perform(impl->Curl);
        resource.reset();
        if (impl->Res != CURLE_OK)
        {
            throw std::runtime_error("curl_easy_perform() failed.\n");
        }
        else
        {
            impl->DownloadMemory = my_str;            
            my_str.clear();
            const auto header1OpenTag = impl->DownloadMemory.find("<h1>");
            const auto header1CloseTag = impl->DownloadMemory.find("</h1>");
            std::string serviceUnavailableError = impl->DownloadMemory.substr(header1OpenTag + 4, header1CloseTag - (header1OpenTag + 4));
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

        const auto unorderedListStart = impl->DownloadMemory.find(unorderedListElementOpen);
        const auto unorderedListEnd = impl->DownloadMemory.find(unorderedListElementClose);
        std::string mealList = impl->DownloadMemory.substr(unorderedListStart, unorderedListEnd - (unorderedListStart + unorderedListElementOpen.size()));
        auto headerMealDelimiter = mealList.find(headerMealNameElement);
        auto headerMealDelimiterEnd = mealList.find("</h2>");
        MealData tmp;
        do
        {
            headerMealDelimiter = mealList.find(headerMealNameElement);
            headerMealDelimiterEnd = mealList.find("</h2>");
            mealName = mealList.substr(headerMealDelimiter + headerMealNameElement.size(), headerMealDelimiterEnd - (headerMealDelimiter + headerMealNameElement.size()));
            if (mealName == terminationMeal)
                break;
            impl->MealsCacheData.insert(std::make_pair(mealName, tmp));
            mealList = mealList.substr(headerMealDelimiterEnd + 5);
        } while (mealName != terminationMeal);

        return true;
    }
    bool MealParser::isGetSuccess()
    {
        return impl->Res == CURLE_OK ? true : false;
    }
    void MealParser::listCacheData()
    {
        if (impl->MealsCacheData.size() == 0)
        {
            std::cout << "Nothing to list." << std::endl;
        }
        else
            for (auto meal : impl->MealsCacheData)
                std::cout << meal.first << std::endl;
    }
    bool MealParser::getDataFromRange(int start, int end)
    {
        bool isInRangeStart = false;
        bool isInRangeEnd = false;
        if (start != end)
        {
            isInRangeStart = getPage(start);
            isInRangeEnd = getPage(end);
        }else{
            bool is_ok = getPage(start);
            parseMeals();
            return is_ok;
        } 
        if (!isInRangeStart || !isInRangeEnd)
        {
            std::cout << "Passed argument is  out of possible range." << std::endl;
            return false;
        }
        else
        {
            for (int i = start; i <= end; i++)
            {
                getPage(i);
                parseMeals();
            }
            return true;
        }
    }

    bool MealParser::findMealInCacheData(std::string meal_name)
    {
        auto isInData = impl->MealsCacheData.find(meal_name);
        if (isInData != impl->MealsCacheData.end())
        {
            std::cout << meal_name << " is found in the cache data." << std::endl;
            return true;
        }
        else
        {
            std::cout << "There no " << meal_name << " in data." << std::endl;
            return false;
        }
    }
    std::unordered_map<std::string, MealData> MealParser::getCacheData() const
    {
        return impl->MealsCacheData;
    }
}

/* TODO */
/* Eliminate Global variable my_string and resource */
