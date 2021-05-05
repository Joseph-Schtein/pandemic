#include "doctest.h"
#include "Board.hpp"
#include "City.hpp"
#include "Color.hpp"
#include "Player.hpp"

#include "Researcher.hpp"
#include "Scientist.hpp"
#include "FieldDoctor.hpp"
#include "GeneSplicer.hpp"
#include "OperationsExpert.hpp"
#include "Dispatcher.hpp"
#include "Medic.hpp"
#include "Virologist.hpp"

using namespace pandemic;

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <set>

using namespace std;


set<City> takeFiveRedCards(){
    set<City> output = {City::Bangkok, City::Beijing, City::Seoul, City::Shanghai, City::Tokyo} ;
    return output;
}


set<City> takeFiveBlueCards(){
    set<City> output = {City::Madrid, City::London, City::Essen, City::Chicago, City::Atlanta} ;
    return output;
}


set<City> takeFiveBlackCards(){
    set<City> output = {City::Mumbai, City::Moscow, City::Riyadh, City::Tehran, City::Delhi} ;
    return output;
}


set<City> takeFiveYellowCards(){
    set<City> output = {City::Johannesburg, City::Bogota, City::Khartoum, City::Santiago, City::SaoPaulo} ;
    return output;
}


TEST_CASE("Check non-special drive"){

    Board b;
    int counter1 = 0;
    int counter2 = 0;
    while(counter1 < 20){
        counter1++;
        City test = static_cast<City>(rand() % 47);
        Dispatcher d = Dispatcher(b ,test);
        while(counter2 < 20){
            counter2++;
            City checkNeighbor = static_cast<City>(rand() % 47); 
            if(b.connection[test].count(checkNeighbor) != 0){
               CHECK_NOTHROW(d.drive(checkNeighbor));
               test = checkNeighbor;
            }

            else{
               CHECK_THROWS(d.drive(checkNeighbor));
            }
        }
    }
}

TEST_CASE("Check medic drive"){

    int counter1 = 0;
    while(counter1 < 20){
        Board b;
        counter1++;
        City test = static_cast<City>(rand() % 47);
        Medic m{b ,test};
        Color co = static_cast<Color>(rand() % 4);
        m.take_card(test);
        m.build();
        if(co == Color::Red){
            set<City> tmp = takeFiveRedCards();
            for(auto var : tmp){
                m.take_card(var);
            }
            
            CHECK_NOTHROW(m.discover_cure(Color::Red));
        }

        if(co == Color::Black){
            set<City> tmp = takeFiveBlackCards();
            for(auto var : tmp){
                m.take_card(var);
            }

           

            CHECK_NOTHROW(m.discover_cure(Color::Black));
        }

        if(co == Color::Blue){
            set<City> tmp = takeFiveBlueCards();
            for(auto var : tmp){
                m.take_card(var);
            }

            
            CHECK_NOTHROW(m.discover_cure(Color::Blue));

        }

        if(co == Color::Yellow){
            set<City> tmp = takeFiveYellowCards();
            for(auto var : tmp){
                m.take_card(var);
            }

            CHECK_NOTHROW(m.discover_cure(Color::Yellow));
        }

        
        City checkNeighbor = static_cast<City>(rand() % 47); 
        int tmp = rand() % 9 + 1;
        b[checkNeighbor] = tmp;
        if(b.connection[test].count(checkNeighbor) != 0){
            CHECK_NOTHROW(m.drive(checkNeighbor));
            if(b.cityColor[checkNeighbor] == co)
                CHECK(b[checkNeighbor] == 0);
                
            else{
                CHECK(b[checkNeighbor] == tmp);
                m.treat(checkNeighbor);
                CHECK(b[checkNeighbor] == 0);
            }
        }

        else{
            CHECK_THROWS(m.drive(checkNeighbor));
            CHECK(b[checkNeighbor] == tmp);
        }
    }
}

TEST_CASE("Check non special fly drict"){
    
    Board b;
    int counter = 0;
    while(counter < 30){
        counter++;
        City test = static_cast<City>(rand() % 47);
        Researcher r = Researcher(b, test);
        City destination = static_cast<City>(rand() % 47);
        if(((double) rand() / (RAND_MAX)) > 0.5 && test != destination){
            r.take_card(destination);
            CHECK_NOTHROW(r.fly_direct(destination));
        }

        else{
            CHECK_THROWS(r.fly_direct(destination));
        }
    }
}

TEST_CASE("Check Dispatcher fly drict"){
    
    Board b;
    int counter = 0;
    while(counter < 30){
        counter++;
        City test = static_cast<City>(rand() % 47);
        Researcher r = Researcher(b, test);
        City destination = static_cast<City>(rand() % 47);
        if(b.existReasearchFacility[test] && test != destination){
            CHECK_NOTHROW(r.fly_direct(destination));
        }

        else{
            CHECK_THROWS(r.fly_direct(destination));
        }
    }
}


TEST_CASE("Check medic fly drict"){
    
    int counter = 0;
    City test = static_cast<City>(rand() % 47);
    while(counter < 30){
        Board b;
        counter++;
        Medic m = Medic(b, test);
        City destination = static_cast<City>(rand() % 47);
        Color co = static_cast<Color>(rand() % 4);
        m.take_card(test);
        m.build();
        if(co == Color::Red){
            set<City> tmp = takeFiveRedCards();
            for(auto var : tmp){
                m.take_card(var);
            }
            
            CHECK_NOTHROW(m.discover_cure(Color::Red));
        }

        if(co == Color::Black){
            set<City> tmp = takeFiveBlackCards();
            for(auto var : tmp){
                m.take_card(var);
            }

            CHECK_NOTHROW(m.discover_cure(Color::Black));
        }

        if(co == Color::Blue){
            set<City> tmp = takeFiveBlueCards();
            for(auto var : tmp){
                m.take_card(var);
            }
            
            CHECK_NOTHROW(m.discover_cure(Color::Blue));

        }

        if(co == Color::Yellow){
            set<City> tmp = takeFiveYellowCards();
            for(auto var : tmp){
                m.take_card(var);
            }

            CHECK_NOTHROW(m.discover_cure(Color::Yellow));
        }
        int tmp = rand() % 9 + 1;
        b[destination] = tmp;
        if(((double) rand() / (RAND_MAX)) + 1 > 0.5 && test != destination){
            if(co == b.cityColor[destination]){
                m.take_card(destination);
                CHECK_NOTHROW(m.fly_direct(destination));
                CHECK(b[destination] == 0);
            }

            else{
                m.take_card(destination);
                CHECK_NOTHROW(m.fly_direct(destination));
                CHECK(b[destination] == tmp);
            }

            test = destination;
        }


        else{
            CHECK(b[destination] == tmp);
            CHECK_THROWS(m.fly_direct(destination));
            CHECK(b[destination] == tmp);
        }
    }
}

TEST_CASE("Check non special fly charter"){
    
    Board b;
    int counter = 0;
    City test = static_cast<City>(rand() % 47);
    Researcher r = Researcher(b, test);
    while(counter < 30){
        counter++;
        City destination = static_cast<City>(rand() % 47);
        if(((double) rand() / (RAND_MAX)) > 0.5 && test != destination){
            r.take_card(test);
            CHECK_NOTHROW(r.fly_charter(destination));
            test = destination;
        }

        else{
            CHECK_THROWS(r.fly_charter(destination));
        }
    }
}




TEST_CASE("Check Operations Expert fly shuttle and build"){
    Board b;
    int counter = 0;
    set<City> choosenCities;
    City tmp;
    while(counter < 25){
        counter++;
        if(((double) rand() / (RAND_MAX)) > 0.5){
            tmp = static_cast<City>(rand() % 47);
            choosenCities.insert(tmp);
        }
    }
    OperationsExpert o{b, tmp};
    CHECK_NOTHROW(o.build());
    for(auto var : choosenCities){
        o.take_card(var);
        CHECK_NOTHROW(o.fly_direct(var));
        CHECK_NOTHROW(o.build());
        
    }

    for(auto var : choosenCities){
        CHECK_NOTHROW(o.fly_shuttle(var));
    }
}


TEST_CASE("Check not special fly shuttle and build"){
    Board b;
    int counter = 0;
    set<City> choosenCities;
    City tmp;
    while(counter < 25){
        counter++;
        if(((double) rand() / (RAND_MAX)) > 0.5){
            tmp = static_cast<City>(rand() % 47);
            choosenCities.insert(tmp);
        }
    }
    GeneSplicer g{b, tmp};
    g.take_card(tmp);
    CHECK_NOTHROW(g.build());
    for(auto var : choosenCities){
        g.take_card(var);
        CHECK_NOTHROW(g.fly_direct(var));
        g.take_card(var);
        CHECK_NOTHROW(g.build());
        
    }

    for(auto var : choosenCities){
        CHECK_NOTHROW(g.fly_shuttle(var));
    }
}


TEST_CASE("Check not special treat"){
    Board b;
    int counter = 0;
    set<City> choosenCities;
    City start = static_cast<City>(rand() % 47);
    b[start] = rand() % 9 + 1;
    City tmp;
    Researcher r{b, start};

    while(counter < 25){
        counter++;
        if(((double) rand() / (RAND_MAX)) > 0.5){
            tmp = static_cast<City>(rand() % 47);
            choosenCities.insert(tmp);
        }
    }

    for(auto var : choosenCities){
        b[var] = rand() % 9 + 1;
    }

   
    for(auto var : choosenCities){
        r.take_card(var);
        CHECK_NOTHROW(r.fly_direct(var));
        int intTmp = b[var];
        CHECK_NOTHROW(r.treat(var));
        CHECK(b[var] == intTmp-1);
    }


}


TEST_CASE("Check Field Doctor treat"){
    Board b;
    int counter = 0;
    set<City> choosenCities;
    City start = static_cast<City>(rand() % 47);
    City tmp;
    FieldDoctor f{b, start};

    while(counter < 25){
        counter++;
        if(((double) rand() / (RAND_MAX)) > 0.5){
            tmp = static_cast<City>(rand() % 47);
            choosenCities.insert(tmp);
        }
    }

    for(auto var : choosenCities){
        b[var] = rand() % 9 + 2;
    }

    for(auto var : choosenCities){
        set<City> nei = b.connection[var];
        for(auto var2 : nei){
            b[var2] = rand() % 9 + 2;
        }
    }

   
    for(auto var : choosenCities){
        f.take_card(var);
        CHECK_NOTHROW(f.fly_direct(var));
        int intTmp = b[var];
        CHECK_NOTHROW(f.treat(var));
        CHECK(b[var] == intTmp-1);
        set<City> nei = b.connection[var];
        for(auto var2 : nei){
            int intTmp2 = b[var2];
            CHECK_NOTHROW(f.treat(var2));
            CHECK(b[var2] == intTmp2-1);
        }
    }
}


TEST_CASE("Check Virologist treat"){

    Board b;
    int counter = 0;
    set<City> choosenCities;
    City start = static_cast<City>(rand() % 47);
    City tmp;
    Virologist v{b, start};

    while(counter < 25){
        counter++;
        if(((double) rand() / (RAND_MAX)) > 0.5){
            tmp = static_cast<City>(rand() % 47);
            choosenCities.insert(tmp);
        }
    }

    for(auto var : choosenCities){
        b[var] = rand() % 9 + 1;
    }

    for(auto var : choosenCities){
        v.take_card(var);
        int intTmp = b[var];
        CHECK_NOTHROW(v.treat(var));
        CHECK(b[var] == intTmp-1);
    }
}


TEST_CASE("Check GeneSplicer discover cure"){

    Board b;
    int counter = 0;
    City start = static_cast<City>(rand() % 47);
    City tmp;
    GeneSplicer g{b, start};
    OperationsExpert o{b, start};

    while(counter < 25){
        counter++;
        if(((double) rand() / (RAND_MAX)) > 0.5){
            tmp = static_cast<City>(rand() % 47);
            o.take_card(tmp);
            o.fly_direct(tmp);
            o.build();
            g.take_card(tmp);
        }
    }
    City tmp2;
    bool foundFacility = false;
    while (!foundFacility){
        tmp2 = static_cast<City>(rand() % 47);
        if(b.existReasearchFacility[tmp2]){
            foundFacility = true;
        }
    }
    g.take_card(tmp2);
    g.fly_direct(tmp2);

    CHECK_NOTHROW(g.discover_cure(Color::Red));
    CHECK_NOTHROW(g.discover_cure(Color::Blue));
    CHECK_NOTHROW(g.discover_cure(Color::Black));
    CHECK_NOTHROW(g.discover_cure(Color::Yellow));

}


TEST_CASE("Check Researcher discover cure"){

    Board b;
    int counter = 0;
    City start = static_cast<City>(rand() % 47);
    Researcher g{b, start};
    
    set<City> tmp1 = takeFiveBlueCards();
    for(auto var : tmp1){
        g.take_card(var);
    }

            
    CHECK_NOTHROW(g.discover_cure(Color::Blue));


    set<City> tmp2 = takeFiveRedCards();
    for(auto var : tmp2){
        g.take_card(var);
    }

            
    CHECK_NOTHROW(g.discover_cure(Color::Red));


    set<City> tmp3 = takeFiveBlackCards();
    for(auto var : tmp3){
        g.take_card(var);
    }

            
    CHECK_NOTHROW(g.discover_cure(Color::Black));


    set<City> tmp4 = takeFiveYellowCards();
    for(auto var : tmp4){
        g.take_card(var);
    }

            
    CHECK_NOTHROW(g.discover_cure(Color::Yellow));
    

    

}





