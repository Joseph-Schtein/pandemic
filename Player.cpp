#include "Player.hpp"

#include <stdlib.h> 
#include <algorithm> 
#include <vector> 
#include <string>      

namespace pandemic{


    const int NUMBER_OF_CARDS = 5;


    Player::Player(Board& board, City name, std::string my_role):
    board(board), currentCity(name), my_job(std::move(my_role)){
        inHand = {};
    }



    Player& Player::fly_direct(City passTo){
        bool doPassToHave = false;
        for(City var : inHand){
            if(var == passTo){
                doPassToHave = true;
            }
        }

        if(doPassToHave && currentCity != passTo){
            this->currentCity = passTo;
            inHand.erase(passTo);
        }

        else{
            throw std::invalid_argument("the needed card is not in the player hand");
        }

        return *this;
    }

    Player& Player::drive(City passTo){
        std::set<City> neighbors = board.getNeighbors(currentCity);

        if(std::find(neighbors.begin(), neighbors.end(), passTo) != neighbors.end() && currentCity != passTo){
            this->currentCity = passTo;
        }

        else{
            throw std::invalid_argument("that city isn't can be reach from: " + board.cityToString[currentCity]+ ", to" + board.cityToString[passTo]);
        }

        return *this;
    }

    Player& Player::fly_charter(City passTo){
        if(this->currentCity == passTo || this->inHand.count(this->currentCity) == 0){
            throw std::invalid_argument("the needed card is not in the player hand or we tried to fly to current city");

        }
    
        this->currentCity = passTo;
        this->inHand.erase(this->currentCity);        
        return *this;
    }

    Player& Player::fly_shuttle(City passTo){
       
        if(currentCity == passTo || !board.existReasearchFacility[passTo] || !board.existReasearchFacility[currentCity]){
            throw std::invalid_argument("you can't fly shuttle because the two cities do not have resarch facility");
        }
        currentCity = passTo; 
        return *this;
    }

    Player& Player::build(){
        if(this->board.existReasearchFacility[currentCity]){
            return *this;
        }

        if(!this->board.existReasearchFacility[currentCity]){
            if(this->inHand.count(this->currentCity) > 0){
                this->board.existReasearchFacility[this->currentCity] = true;
                this->inHand.erase(this->currentCity);
            }
            

            else{
                throw std::invalid_argument("you can't build here because you don't have a card city for it");
            }
        }

        return *this;
        
    }

    Player& Player::discover_cure(Color disease){
        
        int counter = 0;
        if(!board.existCure[disease]){           
            for(auto var : inHand){
                if(disease == board.cityColor[var]){
                    counter++;
                }
            }
        }

        if(!board.existReasearchFacility[this->currentCity] || counter< NUMBER_OF_CARDS){
            throw std::invalid_argument("you can't discover cure in that city because there isn't a research facility here");

        }

        
        for (auto var = inHand.begin(); var != inHand.end(); ){
            if(disease == board.cityColor[*var]){
                var = inHand.erase(var);
                counter--;
            }
            else{
                ++var;
            }

            if(counter <= 0){
                break;
            }
        }

        board.existCure[disease] = true;

    
        return *this;
    }

    Player& Player::treat(City treatCity){

        Color col = board.cityColor[currentCity];
        bool findCure = board.existCure[col];
        int pandStatus = board.cityStatus[currentCity];
        if(pandStatus > 0 && currentCity == treatCity){
            if(!findCure){
                board.cityStatus[currentCity] = board.cityStatus[currentCity] - 1; 
            }

            else{
                board.cityStatus[currentCity] = 0;
            }
        }

        else{
            throw std::invalid_argument("the disease is died already in: " + board.cityToString[treatCity]);
        }    

        return *this;
    }

    Player& Player::take_card(City newCard){     
        this->inHand.insert(newCard); 
        return *this;
    }

    Player& Player::remove_cards(){
        inHand.clear();
        return *this;
    }

    std::string Player::role(){
        return my_job;
    }

}