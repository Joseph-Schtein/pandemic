#include "Virologist.hpp"
#include <algorithm>

namespace pandemic{

    std::string Virologist::role(){
        return "Virologist";
    } 

    Player& Virologist::treat(City treatCity){
        bool findCure = this->board.existCure[this->board.cityColor[this->currentCity]];
        int pandStatus = this->board[treatCity];
        if(pandStatus != 0 && board.cityToString[treatCity] == board.cityToString[this->currentCity]){
            if(!findCure){
                this->board[treatCity] = this->board[treatCity]-1; 
            }

            else{
                this->board[treatCity] = 0;
            }
        }

        else if(pandStatus != 0 && this->inHand.count(treatCity) != 0){
            this->inHand.erase(treatCity);
            if(!findCure){
                this->board[treatCity] = this->board[treatCity]-1; 
            }

            else{
                this->board[treatCity] = 0;
            }

        }

        else{
            throw std::invalid_argument("Virologist can't treat");
        }

        return *this;

    }
}