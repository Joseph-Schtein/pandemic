#include <fstream>
#include <iterator>
#include <sstream>
#include <algorithm>
#include <ostream>
#include <string>

#include "Board.hpp"
#include "City.hpp"
#include "Color.hpp"


namespace pandemic{



    Board::Board(){
        replaceEnumByString();
        std::string line;
        std::string cityName;
        std::string currentCityColor;
        std::string word;
        std::set<City> neigbors;
        std::ifstream myfile;
        myfile.open("cities_map.txt");
        while (std::getline(myfile, line)){
            bool newLine = true;
            bool insertColor = true;
            std::istringstream ss(line);
            while (ss >> word){
                if(newLine){
                    cityName = word;
                    newLine = false;
                }

                else if(insertColor){
                    currentCityColor = word;
                    insertColor = false;
                }

                else{
                    City tmp = stringToCity[word];
                    neigbors.insert(tmp);
                }
            } 
            City cityConvert = stringToCity[cityName];
            cityStatus[cityConvert] = 0;
        
        
            if(currentCityColor == "Black"){
                cityColor.insert(std::make_pair(cityConvert, Color::Black));
            }

            else if(currentCityColor == "Blue"){
                cityColor.insert(std::make_pair(cityConvert, Color::Blue));;
            }

            else if(currentCityColor == "Yellow"){
                cityColor.insert(std::make_pair(cityConvert, Color::Yellow));;
            }

            else if(currentCityColor == "Red"){
                cityColor.insert(std::make_pair(cityConvert, Color::Red));;
            }

            connection.insert(std::make_pair(cityConvert, neigbors));


            neigbors.clear();
            
            
           
        }
    }


    int& Board::operator[](City name){
        if (this->cityStatus[name]==0) {
            this->cityStatus[name] = 0;
        }

        return cityStatus[name];
    };

    std::ostream& operator<<(std::ostream& os, Board& board){
        std::string cityToPrint;
        for(auto& var : board.cityStatus){
            cityToPrint = board.cityToString[var.first];
            os << "City: " << cityToPrint << ", have desis level: " << var.second << std::endl;
        }

        for(auto& var : board.existReasearchFacility){
            std::string tmpCity = board.cityToString[var.first];
            os << "At city: " << tmpCity << ", we build a research facility" << std::endl;
        }

        for(auto& var : board.existCure){
            if(var.first == Color::Black){
                os << "For color Black ";
                if(var.second){
                    os << "we found already cure" << std::endl;
                }
                
                else{
                    os << "we still didn't found cure" << std::endl;
                }
            }

            if(var.first == Color::Blue){
                os << "For color Blue ";
                if(var.second){
                    os << "we found already cure" << std::endl ;
                }
            
                else{
                    os << "we still didn't found cure" << std::endl;
                }
            }

            if(var.first == Color::Red){
                os << "For color Red ";
                if(var.second){
                    os << "we found already cure" << std::endl;
                }
            
                else{
                    os << "we still didn't found cure" << std::endl;
                }
            }

            if(var.first == Color::Yellow){
                os << "For color Yellow ";
                if(var.second){
                    os << "we found already cure" << std::endl;
                }
                
                else{
                    os << "we still didn't found cure" << std::endl;
                }
            }


        }
    
        return os;  
    }



    bool Board::is_clean(){
        bool found = false;
        for(auto& var : cityStatus){
            if(var.second > 0){
                found = true;
            }
        }

        return !found;
    }

    void Board::remove_cures(){
        for(auto& var : existCure){
            var.second = false;
        }   
    }

    void Board::remove_stations(){
        for(auto& var : existReasearchFacility){
            var.second = false;
        }
    }



    std::set<City> Board::getNeighbors(const City& cityName){
        return connection[cityName];
    }

    bool Board::haveFacility(City cityName){
        return existReasearchFacility.at(cityName);
    }

    void Board::buildResearchFacility(City cityName){
        existReasearchFacility.at(cityName) = true;
    }

    Color Board::getCityColor(City cityName){
        return this->cityColor[cityName];
    }

    bool Board::haveCure(Color colorType){
        return this->existCure[colorType];
    } 


    void Board::replaceEnumByString(){
        stringToCity = {{"Algiers", City::Algiers},
                        {"Atlanta", City::Atlanta},
                        {"Baghdad", City::Baghdad},
                        {"Bangkok", City::Bangkok},
                        {"Beijing", City::Beijing},
                        {"Bogota", City::Bogota},
                        {"BuenosAires", City::BuenosAires},
                        {"Cairo", City::Cairo},
                        {"Chennai", City::Chennai},
                        {"Chicago", City::Chicago},
                        {"Delhi", City::Delhi},
                        {"Essen", City::Essen},
                        {"HoChiMinhCity", City::HoChiMinhCity},
                        {"HongKong", City::HongKong},
                        {"Istanbul", City::Istanbul},
                        {"Jakarta", City::Jakarta},
                        {"Johannesburg", City::Johannesburg},
                        {"Karachi", City::Karachi},
                        {"Khartoum", City::Khartoum},
                        {"Kinshasa", City::Kinshasa},
                        {"Kolkata", City::Kolkata},
                        {"Lagos", City::Lagos},
                        {"Lima", City::Lima},
                        {"London", City::London},
                        {"LosAngeles", City::LosAngeles},
                        {"Madrid", City::Madrid},
                        {"Manila", City::Manila},
                        {"MexicoCity", City::MexicoCity},
                        {"Miami", City::Miami},
                        {"Milan", City::Milan},
                        {"Montreal", City::Montreal},
                        {"Moscow", City::Moscow},
                        {"Mumbai", City::Mumbai},
                        {"NewYork", City::NewYork},
                        {"Osaka", City::Osaka},
                        {"Paris", City::Paris},
                        {"Riyadh", City::Riyadh},
                        {"SanFrancisco", City::SanFrancisco},
                        {"Santiago", City::Santiago},
                        {"SaoPaulo", City::SaoPaulo},
                        {"Seoul", City::Seoul},
                        {"Shanghai", City::Shanghai},
                        {"StPetersburg", City::StPetersburg},
                        {"Sydney", City::Sydney},
                        {"Taipei", City::Taipei},
                        {"Tehran", City::Tehran},
                        {"Tokyo", City::Tokyo},
                        {"Washington", City::Washington}};

        cityToString = {{City::Algiers, "Algiers"},
                        {City::Atlanta, "Atlanta"},
                        {City::Baghdad, "Baghdad"},
                        {City::Bangkok, "Bangkok"},
                        {City::Beijing, "Beijing"},
                        {City::Bogota, "Bogota"},
                        {City::BuenosAires, "BuenosAires"},
                        {City::Cairo, "Cairo"},
                        {City::Chennai, "Chennai"},
                        {City::Chicago, "Chicago"},
                        {City::Delhi, "Delhi"},
                        {City::Essen, "Essen"},
                        {City::HoChiMinhCity, "HoChiMinhCity"},
                        {City::HongKong, "HongKong"},
                        {City::Istanbul, "Istanbul"},
                        {City::Jakarta, "Jakarta"},
                        {City::Johannesburg, "Johannesburg"},
                        {City::Karachi, "Karachi"},
                        {City::Khartoum, "Khartoum"},
                        {City::Kinshasa, "Kinshasa"},
                        {City::Kolkata, "Kolkata"},
                        {City::Lagos, "Lagos"},
                        {City::Lima, "Lima"},
                        {City::London, "London"},
                        {City::LosAngeles, "LosAngeles"},
                        {City::Madrid, "Madrid"},
                        {City::Manila, "Manila"},
                        {City::MexicoCity, "MexicoCity"},
                        {City::Miami, "Miami"},
                        {City::Milan, "Milan"},
                        {City::Montreal, "Montreal"},
                        {City::Moscow, "Moscow"},
                        {City::Mumbai, "Mumbai"},
                        {City::NewYork, "NewYork"},
                        {City::Osaka, "Osaka"},
                        {City::Paris, "Paris"},
                        {City::Riyadh, "Riyadh"},
                        {City::SanFrancisco, "SanFrancisco"},
                        {City::Santiago, "Santiago"},
                        {City::SaoPaulo, "SaoPaulo"},
                        {City::Seoul, "Seoul"},
                        {City::Shanghai, "Shanghai"},
                        {City::StPetersburg, "StPetersburg"},
                        {City::Sydney, "Sydney"},
                        {City::Taipei, "Taipei"},
                        {City::Tehran, "Tehran"},
                        {City::Tokyo, "Tokyo"},
                        {City::Washington, "Washington"}};


        existReasearchFacility = {  {City::Algiers, false},
                                    {City::Atlanta, false},
                                    {City::Baghdad, false},
                                    {City::Bangkok, false},
                                    {City::Beijing, false},
                                    {City::Bogota, false},
                                    {City::BuenosAires, false},
                                    {City::Cairo, false},
                                    {City::Chennai, false},
                                    {City::Chicago, false},
                                    {City::Delhi, false},
                                    {City::Essen, false},
                                    {City::HoChiMinhCity,false},
                                    {City::HongKong, false},
                                    {City::Istanbul, false},
                                    {City::Jakarta, false},
                                    {City::Johannesburg, false},
                                    {City::Karachi, false},
                                    {City::Khartoum, false},
                                    {City::Kinshasa, false},
                                    {City::Kolkata, false},
                                    {City::Lagos, false},
                                    {City::Lima, false},
                                    {City::London, false},
                                    {City::LosAngeles, false},
                                    {City::Madrid, false},
                                    {City::Manila, false},
                                    {City::MexicoCity, false},
                                    {City::Miami, false},
                                    {City::Milan, false},
                                    {City::Montreal, false},
                                    {City::Moscow, false},
                                    {City::Mumbai, false},
                                    {City::NewYork, false},
                                    {City::Osaka, false},
                                    {City::Paris, false},
                                    {City::Riyadh, false},
                                    {City::SanFrancisco, false},
                                    {City::Santiago, false},
                                    {City::SaoPaulo, false},
                                    {City::Seoul,false},
                                    {City::Shanghai, false},
                                    {City::StPetersburg, false},
                                    {City::Sydney, false},
                                    {City::Taipei, false},
                                    {City::Tehran, false},
                                    {City::Tokyo, false},
                                    {City::Washington, false}};  

        existCure = {{Color::Black, false},
                     {Color::Blue, false},
                     {Color::Yellow, false},
                     {Color::Red, false}};

        colorToString = {{Color::Black, "Black"},
                        {Color::Blue, "Blue"},
                        {Color::Red, "Red"},
                        {Color::Yellow, "Yellow"}};
         
    }
}    