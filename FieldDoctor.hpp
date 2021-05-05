#pragma once


#include "City.hpp"
#include "Color.hpp"
#include "Board.hpp"
#include "Player.hpp"

#include <string>

namespace pandemic{

    class FieldDoctor : public Player{
        
        public:

        FieldDoctor(Board& board, City currentCity): Player(board, currentCity, "FieldDoctor"){}

        ~FieldDoctor() {}

        Player& treat(City treatCity) override;

        std::string role() override;
    };

}

