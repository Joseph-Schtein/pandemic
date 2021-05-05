#include "OperationsExpert.hpp"

namespace pandemic{

    std::string OperationsExpert::role(){
        return "OperationsExpert";
    }

    Player& OperationsExpert::build(){
        if(!board.existReasearchFacility[currentCity]){
            board.existReasearchFacility[currentCity] = true;
        }

        return *this;
    }
}
