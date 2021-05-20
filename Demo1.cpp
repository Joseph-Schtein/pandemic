/**
 * Demo program for Pandemic exercise - OperationsExpert role
 * 
 * Author: Erel Segal-Halevi
 * Since : 2021-04
 */

#include "Board.hpp"
#include "City.hpp"
#include "Color.hpp"

#include "OperationsExpert.hpp"

using namespace pandemic;

#include <iostream>
#include <stdexcept>
using namespace std;

int main() {
	Board board;  // Initialize an empty board
	board[City::Kinshasa] = 2;      // put 2 yellow disease cubes in Kinshasa
	board[City::MexicoCity] = 3;    // put 3 yellow disease cubes in MexicoCity
	board[City::HoChiMinhCity] = 1; // put 1 red disease cube in HoChiMinhCity
	board[City::Chicago] = 1;      // put 1 blue disease cube in Chicago
	
	OperationsExpert r {board, City::Atlanta};  // initialize an "operations expert" player on the given board, in Atlanta.
	r.take_card(City::Atlanta)
	 .take_card(City::Johannesburg)
	 .take_card(City::Khartoum)
	 .take_card(City::SaoPaulo)
	 .take_card(City::BuenosAires)
	 .take_card(City::HoChiMinhCity);


	/* build action */

	r.build();  // legal action: you discard the Atlanta card and build a research station in Atlanta.

	/* drive action */

	r.drive(City::Washington);  // legal action: you drive from Atlanta to a connected city.
	try {
		r.drive(City::Madrid);  // illegal action: Madrid is not connected to Washington.
	} catch (const exception& ex) {
	 	cout << "caught exception: " << ex.what() << endl;  // prints a meaningful error message.
	}

	/* fly_direct action */
	
	r.fly_direct(City::Johannesburg);  // legal action: you discard the Johannesburg card and fly to Johannesburg.
	try {
		r.fly_direct(City::Taipei);  // illegal action: you do not have the card of Taipei.
	} catch (const exception& ex) {
		cout << "caught exception: " << ex.what() << endl;  // prints a meaningful error message.
	}


	/* treat action */

	r.drive(City::Kinshasa);    // legal action: you move from Johannesburg to a connected city.
	cout << board[City::Kinshasa] << endl; // 2
	r.treat(City::Kinshasa);    // legal action: you remove 1 disease cube from current city (1 cube remains).
	cout << board[City::Kinshasa] << endl; // 1
	r.treat(City::Kinshasa);    // legal action: you remove 1 disease cube from current city (0 cubes remain).
	cout << board[City::Kinshasa] << endl; // 0
	try {
		r.treat(City::Kinshasa);  // illegal action: no more cubes remain in Kinshasa.
	} catch (const exception& ex) {
	 	cout << "caught exception: " << ex.what() << endl;  // prints a meaningful error message.
	}
	try {
		r.treat(City::Washington);  // illegal action: you are not in Washington.
	} catch (const exception& ex) {
	 	cout << "caught exception: " << ex.what() << endl;  // prints a meaningful error message.
	}


	/* fly_charter action */

	r.drive(City::Khartoum)
	 .fly_charter(City::Sydney);  // legal action: you discard the Khartoum card and fly to Sydney.

	try {
		r.fly_charter(City::Seoul);  // illegal action: you do not have the Sydney card (the card of the city you are in).
	} catch (const exception& ex) {
	 	cout << "   caught exception: " << ex.what() << endl;  // prints a meaningful error message.
	}


	/* build action */
	
	r.drive(City::LosAngeles);  // legal action: note that LosAngeles is connected to Sydney.
	r.build();     // legal action: build a research station in LosAngeles.
		// NOTE: you do not have the LosAngeles card, so for other roles this would throw an exception.
		//       But for the OperationsExpert it is legal, since he may build a research station without a card.
		


	/* fly_shuttle action */

	r.fly_shuttle(City::Atlanta); // legal action: you fly from one research station to another.
	r.fly_shuttle(City::LosAngeles); // legal action: you fly from one research station to another.
	try {
		r.fly_shuttle(City::Chicago); // illegal action: there is no research station in Chicago.
	} catch (const exception& ex) {
	 	cout << "caught exception: " << ex.what() << endl;  // prints a meaningful error message.
	}


	/* discover_cure action */
	try {
		r.discover_cure(Color::Yellow); // illegal action: you only have 2 yellow cards remaining.
	} catch (const exception& ex) {
	 	cout << "caught exception: " << ex.what() << endl;  // prints a meaningful error message.
	}
	
	r.take_card(City::Miami)
	 .take_card(City::Bogota)
	 .take_card(City::Lima);

	r.discover_cure(Color::Yellow); // legal action: you discard 5 yellow cards and discover a yellow cure.
	try {
		r.fly_direct(City::Miami); // illegal action: you discarded the Miami card to discover a cure, so you cannot use this card.
	} catch (const exception& ex) {
	 	cout << "caught exception: " << ex.what() << endl;  // prints a meaningful error message.
	}

	cout << board[City::MexicoCity] << endl;
	/* treat action after discovering a cure */
	r.treat(City::MexicoCity);   // you now remove ALL disease cubes from MexicoCity, since there is a yelllow cure.


	/* clean the board */

	cout << board << endl;  // print the board in any reasonable format.
	cout << board.is_clean() << endl;  // print "0" - the board is not clean.
	
	r.drive(City::Chicago)
	 .treat(City::Chicago)
     .fly_direct(City::HoChiMinhCity)
	 .treat(City::HoChiMinhCity);

	cout << board << endl;  // prints the board in any reasonable format.
	cout << board.is_clean() << endl;  // prints "1" - the board is clean - congratulations!!! You cured all diseases!!!
}

