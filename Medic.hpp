#pragma once


#include "City.hpp"
#include "Color.hpp"
#include "Board.hpp"
#include "Player.hpp"

#include <string>

namespace pandemic{

    class Medic : public Player{
        
        public:

        Medic(Board& board, City currentCity): Player(board, currentCity, "Medic"){}

        ~Medic(){}

        Player& treat(City treatCity) override;

        Player& drive(City passTo) override;
        
        Player& fly_direct(City passTo) override;

        Player& fly_charter(City passTo) override;

        Player& fly_shuttle(City passTo) override;

        std::string role() override;
    };

}

