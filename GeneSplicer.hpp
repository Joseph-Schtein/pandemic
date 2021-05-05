#pragma once


#include "City.hpp"
#include "Color.hpp"
#include "Board.hpp"
#include "Player.hpp"

#include <string>

namespace pandemic{

    class GeneSplicer : public Player{
        
        public:

        GeneSplicer(Board& board, City currentCity): Player(board, currentCity, "GeneSplicer"){}

        ~GeneSplicer() {}

        Player& discover_cure(Color disease) override;

        std::string role() override;
    };

}
