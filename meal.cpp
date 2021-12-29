#include "meal.h"

Meal::Meal(Meals meal) {
    switch (meal){
        case Meals::Spagetti:
            name = "Spagetti";
        case Meals::Pizza:
            name = "Pizza";
        case Meals::Fish_and_Chips:
            name = "Fish and Chips";
        case Meals::Rice_and_chicken:
            name = "Rice and chicken";
        case Meals::Salmon:
            name = "Salmon";
        case Meals::Roasted_beef:
            name = "Roasted beef";
        case Meals::Sushi:
            name = "Sushi";
    }
}

std::string Meal::get_name() const{
    return this->name;   
}