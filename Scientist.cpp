#include "Scientist.hpp"

namespace pandemic{

    std::string Scientist::role(){
        return "Scientist";
    }

    Player& Scientist::discover_cure(Color disease){
        int counter = 0;
        for(auto var : inHand){
            if(disease == board.cityColor[var]){
                counter++;
            }
        }

        if(!board.existReasearchFacility[currentCity] || counter < neededCards){
            throw std::invalid_argument("you can't discover cure in that city because there isn't a research facility here");
        }

        if(board.existCure[disease]){
            return *this;
        }

        
        if(counter >= neededCards){
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

        board.existCure[disease] = true;
        return *this;
    }
};