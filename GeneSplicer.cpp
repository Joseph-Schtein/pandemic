#include "GeneSplicer.hpp"

const int NUMBER_OF_CARDS = 5;

namespace pandemic{

    Player& GeneSplicer::discover_cure(Color disease){
        int counter = this->inHand.size();          
        

        if(!board.existReasearchFacility[this->currentCity] || counter< NUMBER_OF_CARDS){
            throw std::invalid_argument("you can't discover cure in that city because there isn't a research facility here");

        }

        
        for (auto var = inHand.begin(); var != inHand.end(); ){
            
            var = inHand.erase(var);
            counter--;

            if(counter <= 0){
                break;
            }
        }

        board.existCure[disease] = true;

    
        return *this;
    }

    std::string GeneSplicer::role(){
        return "GeneSplicer";
    }
};
