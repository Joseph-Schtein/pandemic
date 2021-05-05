#include "FieldDoctor.hpp"
namespace pandemic{

    std::string FieldDoctor::role(){
        return "FieldDoctor";
    }


    Player& FieldDoctor::treat(City treatCity){
        bool found = false;
        if (this->currentCity == treatCity){
            found = true;
        }

        else if(!found){
            for (auto nei : board.connection[this->currentCity]){
                if(nei==treatCity){
                    found = true;

                }  
            }   
        }

        if(!found || board[treatCity] == 0){    
            throw std::invalid_argument("FieldDoctor can't treat");
        
        }

        if (board.existCure[board.cityColor[treatCity]]) {
            board[treatCity] = 0;
            return *this;
        }

        board[treatCity]--;
        return *this;
    }
};