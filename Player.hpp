#pragma once

#include <set>

#include "City.hpp"
#include "Color.hpp"
#include "Board.hpp"


namespace pandemic{

    class Player{
        public:
            City currentCity;
            Board& board;
            std::set<City> inHand;
            std::string my_job;


            Player(Board& board, City name, std::string my_role);

            ~Player() {}

            virtual Player& drive(City passTo);

            virtual Player& fly_direct(City passTo);

            virtual Player& fly_charter(City passTo);

            virtual Player& fly_shuttle(City passTo);

            virtual Player& build();

            virtual Player& discover_cure(Color disease);

            virtual Player& treat(City treatCity);

            virtual std::string role();

            Player& take_card(City newCard);

            Player& remove_cards();

    };

}
