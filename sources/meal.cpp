#include "../headers/meal.h"

Meal::Meal(Meals meal) {
    switch (meal){
        case Meals::Spagetti:
            name = "Spagetti";
            break;
        case Meals::Pizza:
            name = "Pizza";
            break;
        case Meals::Fish_and_Chips:
            name = "Fish and Chips";
            break;
        case Meals::Rice_and_chicken:
            name = "Rice and chicken";
            break;
        case Meals::Salmon:
            name = "Salmon";
            break;
        case Meals::Roasted_beef:
            name = "Roasted beef";
            break;
        case Meals::Sushi:
            name = "Sushi";
            break;
        default :
            throw std::out_of_range("Constructor argument is out of Meals enumerators range .");
    }
}


std::string Meal::get_name() const{
    return this->name;   
}
