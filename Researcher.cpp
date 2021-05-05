#include "Researcher.hpp"

namespace pandemic{

const int NUMBER_OF_CARDS = 5;

    std::string Researcher::role(){
        return "Researcher";
    }

    Player& Researcher::discover_cure(Color disease){
        int counter = 0;
        for(auto var : inHand){
            if(disease == board.cityColor[var]){
                counter++;
            }
        }

        if(counter >= NUMBER_OF_CARDS){
            for (auto var = inHand.begin(); var != inHand.end(); ){
                if(disease == board.cityColor[*var]){
                    var = inHand.erase(var);
                    counter--;
                }
                else{
                    ++var;
                }

                if(counter <= 0){
                    break;
                }
            }
        }

        else{
            throw std::invalid_argument("you can't discover cure in that city because there isn't a research facility here");
        }
        board.existCure[disease] = true;

    
        return *this;
    }
};