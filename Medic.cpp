#include "Medic.hpp"

namespace pandemic{

    std::string Medic::role(){
        return "Medic";
    }

    Player& Medic::treat(City treatCity){
        if(board.cityToString[currentCity] != board.cityToString[treatCity] || this->board[currentCity] == 0){
            throw std::invalid_argument("Medic can't treat");
        }

        this->board[this->currentCity] = 0;
        return *this;
    }

    Player& Medic::drive(City passTo){
        Player::drive(passTo);
        if(this->board.existCure[this->board.cityColor[passTo]]){
            this->board[passTo] = 0;
        }

        return *this;
    }

    Player& Medic::fly_direct(City passTo){
        Player::fly_direct(passTo);
        if(this->board.existCure[this->board.cityColor[passTo]]){
            this->board[passTo] = 0;
        }

        return *this;
    }

    Player& Medic::fly_charter(City passTo){
        Player::fly_charter(passTo);
        if(this->board.existCure[this->board.cityColor[passTo]]){
            this->board[passTo] = 0;
        }

        return *this;
    }

     Player& Medic::fly_shuttle(City passTo){
        Player::fly_shuttle(passTo);
        if(this->board.existCure[this->board.cityColor[passTo]]){
            this->board[passTo] = 0;
        }

        return *this;
    }
};    