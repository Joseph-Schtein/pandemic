#include "Dispatcher.hpp"
#include <algorithm>

namespace pandemic{

    std::string Dispatcher::role(){
        return "Dispatcher";
    }

    Player& Dispatcher::fly_direct(City passTo){
        bool doCurrentCityHave = this->board.existReasearchFacility[this->currentCity];
        bool sameCity = this->currentCity == passTo;
        int doPassToHave = this->inHand.count(passTo);

        if(doCurrentCityHave && !sameCity){
            this->currentCity = passTo;
        }


        else if(doPassToHave != 0 && !sameCity){
            this->currentCity = passTo;
            this->inHand.erase(passTo);
        }
        

        else{
           
            throw std::invalid_argument("you can't fly direct because there is no resarch facility or city card");
        }

        return *this;
    }
}