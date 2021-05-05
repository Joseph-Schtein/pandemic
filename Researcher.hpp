#pragma once


#include "City.hpp"
#include "Color.hpp"
#include "Board.hpp"
#include "Player.hpp"

#include <string>

namespace pandemic{

    class Researcher : public Player{
        
        public:

        Researcher(Board& board, City currentCity): Player(board, currentCity, "Researcher"){}

        ~Researcher() {}

        Player& discover_cure(Color disease) override;

        std::string role() override;
    };

}
