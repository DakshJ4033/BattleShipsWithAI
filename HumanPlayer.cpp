//
// Created by Beast PC on 5/21/2021.
//
#include "HumanPlayer.h"
#include <sstream>
//this function is used to check whether or not the coordinates were valid or not for placing the ship
bool BattleShip::HumanPlayer::check_valid_pos(int ship_length) {
    //  if ship choice is "h" then we check if we can place the ship horizontally else check vertical
    bool horizontalvalid;
    if (this->retrieveshipchoice() == "h") {
        horizontalvalid = check_horizontal(ship_length);
    }
    else if (this->retrieveshipchoice() == "v") {
        horizontalvalid = check_vertical(ship_length);
    }
    return horizontalvalid;
}

bool BattleShip::HumanPlayer::place_ship(int ship_length, char shipsymbol) {
    bool check_position;
    if (!check_valid_pos(ship_length)) {
        //check if the position is not valid, then we couldn't have placed the ships;
        return false;
    }
    else if (check_valid_pos(ship_length)) {
        if (this->retrieveshipchoice() == "h") {
            //we place the ships horizontally with this function
            check_position = place_horizontal(ship_length, shipsymbol);
            return check_position;
        }
        else if (this->retrieveshipchoice() == "v") {
            //we place the ships vertically
            check_position = place_vertical(ship_length, shipsymbol);
            return check_position;
        }
        return true;
        //We return true when we've successfully placed the ships.
    }
    return false;
}

//We parsed the input into xcoord and ycoord, which represent the valid
//row and column of the ship placement.
//This function checks first if we can read a row, and if we can, try reading the column
//If we were able to read the column, read whatever is left. IF nothing is left, we can save those coords as valid
bool BattleShip::HumanPlayer::get_valid_ship_pos(char shipSymbol, int length) {
    std::string line;
    while (true) {
        std::cout << this->getName() << ", enter the row and column you want to place " << shipSymbol << ", which is " <<
                  length << " long, at with a space in between row and col: ";
        getline(std::cin, line); //grabs the entire line
        std::stringstream line2parse(line);
        int xcoord;
        int ycoord;
        line2parse >> xcoord;
        if (line2parse) { //if I was able to read the number
            line2parse >> ycoord;
            if (line2parse) {
                std::string what_is_left;
                line2parse >> what_is_left;
            }
            if (!line2parse) { //if there is nothing left we will fail to read it
                this->setshipcordrow(xcoord);
                this->setshipcordcol(ycoord);
                return true;
            }
        }
    }
}

std::string BattleShip::HumanPlayer::get_valid_ship(const std::string &prompt, char shipSymbol) {
    std::string line;
    while (true) {
        std::cout << this->getName() << ", do you want to place " << shipSymbol << " horizontally or vertically?" << std::endl;
        std::cout << prompt;
        getline(std::cin, line); //grabs the entire line
        std::stringstream line2parse(line);
        std::string shiporientation;
        line2parse >> shiporientation;
        if (line2parse) { //if I was able to read the number
            std::string what_is_left;
            line2parse >> what_is_left;
            if (!line2parse) { //if there is nothing left we will fail to read it
                for (int i = 0; i < shiporientation.size(); i++) {
                    shiporientation.at(i) = tolower(shiporientation.at(i));
                }
                if (shiporientation == "h" || shiporientation == "v") {
                    return shiporientation;
                }
            }
        }
    }
}

//We needed to distinguish between getting out of bounds firing placement vs just
//outright invalid input like putting george for firingrow and firingcol.
//If it's valid, just exit out of the loop and return but otherwise print placement and firing
void BattleShip::HumanPlayer::get_valid_firing_placement(Board& theboard, Game& game) {
    std::string line;
    while (true) {
        std::cout << this->getName() << ", where would you like to fire?" << std::endl;
        std::cout << "Enter your attack coordinate in the form row col: ";
        getline(std::cin, line); //grabs the entire line
        std::stringstream line2parse(line);
        int xcoord;
        int ycoord;
        line2parse >> xcoord;
        if (line2parse) { //if I was able to read the number
            line2parse >> ycoord;
            if (line2parse) {
                std::string what_is_left;
                line2parse >> what_is_left;
            }
            if (!line2parse) { //if there is nothing left we will fail to read it
                this->setfirecordrow(xcoord);
                this->setfirecordcol(ycoord);
                if (this->validfiringmovecord()) {
                    return;
                } else {
                    std::cout << this->getName() << "'s Firing Board" << std::endl;
                    if (type == "Player 1") {
                        theboard.print_firing_board(game.players.at(0));
                    }
                    else {
                        theboard.print_firing_board(game.players.at(1));
                    }
                    std::cout << this->getName() << "'s Placement Board" << std::endl;
                    if (type == "Player 1") {
                        theboard.print_placement_board(game.players.at(0));
                    }
                    else {
                        theboard.print_placement_board(game.players.at(1));
                    }
                }
            }
        }
    }
}

std::string BattleShip::HumanPlayer::set_ship_choice(char shipSymbol) {
    //  prompts user to enter if they want to place their ship horizontally or vertically
    std::string prompt = "Enter h for horizontal or v for vertical\n"
                         "Your choice: ";
    return get_valid_ship(prompt, shipSymbol);
}

void BattleShip::HumanPlayer::SetupBattleShips(Game& game, std::string prompt, Board& boardfunc) {
    //  sets up battleship for human player by getting their name and making them set their ships
    this->PlayerName = game.get_valid_name(prompt);
    bool validcords = false;
    if (type == "Player 1") {
        boardfunc.print_placement_board(game.players.at(0));
    }
    else {
        boardfunc.print_placement_board(game.players.at(1));
    }
    for (const auto& ships: getShipInfo()) {
        do {
            this->setshipchoice(set_ship_choice(ships.first));
            if (get_valid_ship_pos(ships.first, ships.second)) {
                validcords = place_ship(ships.second, ships.first);
            }
        } while(!validcords);
        if (type == "Player 1") {
            boardfunc.print_placement_board(game.players.at(0));
        }
        else {
            boardfunc.print_placement_board(game.players.at(1));
        }
    }
}

void BattleShip::HumanPlayer::setrandomcoords() {
    //  useless function
    ;
}
