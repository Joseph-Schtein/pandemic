#pragma once


#include <iostream>
#include <string>
#include <set>
#include <map>
#include <utility>
#include <ostream>

#include "City.hpp"
#include "Color.hpp"


namespace pandemic{

    struct Board{    
        std::map<City, int> cityStatus;
            
        std::map<City, Color> cityColor;
            
        std::map<City, std::set<City>> connection;
            
        std::map<City, bool> existReasearchFacility;

        std::map<Color, bool> existCure;

        std::map<std::string, City> stringToCity;

        std::map<City, std::string> cityToString;

        std::map<Color, std::string> colorToString;
            
        Board();

        void replaceEnumByString();
        
        int& operator[](City name);

        friend std::ostream& operator<<(std::ostream& os, Board& board);

        bool is_clean();

        std::set<City> getNeighbors(const City& cityName);

        bool haveFacility(City cityName);

        void buildResearchFacility(City cityName);

        bool haveCure(Color colorType); 

        Color getCityColor(City cityName);

        void remove_cures();

        void remove_stations();

    };
}

