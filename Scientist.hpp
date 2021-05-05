#pragma once


#include "City.hpp"
#include "Color.hpp"
#include "Board.hpp"
#include "Player.hpp"

#include <string>

namespace pandemic{

    class Scientist : public Player{
        public:

        int neededCards;

        Scientist(Board& board, City currentCity, int operationCards): 
        Player(board, currentCity, "Scientist"), neededCards(operationCards){}

        ~Scientist(){}

        Player& discover_cure(Color disease) override;

        std::string role() override;
    };

}

