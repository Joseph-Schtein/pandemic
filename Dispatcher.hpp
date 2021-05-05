#pragma once


#include "City.hpp"
#include "Color.hpp"
#include "Board.hpp"
#include "Player.hpp"

#include <string>

namespace pandemic{

    class Dispatcher : public Player{
        
        public:

        Dispatcher(Board& board, City currentCity): Player(board, currentCity, "Dispatcher"){}

        ~Dispatcher() {}

        Player& fly_direct(City passTo) override;

        std::string role() override;
    };

}

