#pragma once


#include "City.hpp"
#include "Color.hpp"
#include "Board.hpp"
#include "Player.hpp"

#include <string>

namespace pandemic{

    class OperationsExpert : public Player{
        
        public:

        OperationsExpert(Board& board, City currentCity): Player(board, currentCity, "OperationsExpert"){}

        ~OperationsExpert() {}

        Player& build() override;

        std::string role() override;
    };

}

