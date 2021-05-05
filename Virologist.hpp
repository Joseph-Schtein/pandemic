#pragma once


#include "City.hpp"
#include "Color.hpp"
#include "Board.hpp"
#include "Player.hpp"

#include <string>

namespace pandemic{

    class Virologist : public Player{
        
        public:

        Virologist(Board& board, City currentCity): Player(board, currentCity, "Virologist"){}

        ~Virologist(){}

        Player& treat(City treatCity) override;

        std::string role() override;
    };

}

