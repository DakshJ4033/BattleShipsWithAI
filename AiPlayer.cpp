//
// Created by Beast PC on 5/21/2021.
//
#include "AiPlayer.h"
#include <sstream>

std::mt19937 BattleShip::AiPlayer::gen;
//  declaring our static generator so we don't have a undefined reference

int BattleShip::AiPlayer::generatehorizontalvertical(std::mt19937& thegenerator) {
    //  gets 0 or 1 "randomly"
    std::uniform_int_distribution<int> distribution(0, 1);
    return distribution(thegenerator);
}

void BattleShip::AiPlayer::assign_gen(bool seedval, int seed) {
    //  sets the seed for our random number generator
    if (!seedval) {
        gen.seed(time(nullptr));
    }
    else {
        gen.seed(seed);
    }
}

int BattleShip::AiPlayer::generaterow(std::mt19937& thegenerator, int length) {
    //  generates random column to place ship based on ship orientation
    //  only generates valid positions as well
    if (this->shiporientation == "h") {
        std::uniform_int_distribution<int> distribution(0, this->getRows() - 1);
        return distribution(thegenerator);
    } else {
        std::uniform_int_distribution<int> distribution(0, this->getRows() - length);
        return distribution(thegenerator);
    }
}

int BattleShip::AiPlayer::generatecol(std::mt19937& thegenerator, int length) {
    //  generates random column to place ship based on ship orientation
    //  only generates valid positions as well
    if (this->shiporientation == "h") {
        std::uniform_int_distribution<int> distribution(0, this->getCols() - length);
        return distribution(thegenerator);
    } else {
        std::uniform_int_distribution<int> distribution(0, this->getCols() - 1);
        return distribution(thegenerator);
    }
}

//We parsed the input into xcoord and ycoord, which represent the valid
//row and column of the ship placement.
//This function checks first if we can read a row, and if we can, try reading the column
//If we were able to read the column, read whatever is left. IF nothing is left, we can save those coords as valid
bool BattleShip::AiPlayer::get_valid_ship_pos(char shipsymbol, int length) {
    int xcoord;
    int ycoord;

    xcoord = generaterow(gen, length);
    ycoord = generatecol(gen, length);

    this->setshipcordrow(xcoord);
    this->setshipcordcol(ycoord);
    return true;
}

std::string BattleShip::AiPlayer::get_AI_orientation() {
    //  calls generatehorizontalvertical in order to get a 0 or 1. If we get a 0 we set
    //  our orientation to be horizontal else vertical
    if (generatehorizontalvertical(gen) == 0) {
        this->shiporientation = "h";
        return shiporientation;
    } else {
        this->shiporientation = "v";
        return shiporientation;
    }
    return shiporientation;
}

bool BattleShip::AiPlayer::check_valid_pos(int ship_length) {
    //  if shipchoice is "h" then we check if we can place the ship horizontally
    bool horizontalvalid;
    if (this->retrieveshipchoice() == "h") {
        horizontalvalid = check_horizontal(ship_length);
    }
    else if (this->retrieveshipchoice() == "v") {
        horizontalvalid = check_vertical(ship_length);
    }
    return horizontalvalid;
}

bool BattleShip::AiPlayer::place_ship(int ship_length, char shipsymbol) {
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

std::string BattleShip::AiPlayer::set_ship_choice(char shipSymbol) {
    //  calls get_AI_orientation to get "h" or "v" randomly
    return get_AI_orientation();
}

void BattleShip::AiPlayer::SetupBattleShips(Game& game, std::string prompt, Board& boardfunc) {
    //  sets up battleship automatically for AI's and sets their name as well
    //  prints their board after every ship placement
    if (type == "AIPlayer 1" && numInstances == 1) {
        this->setName("AI 1");
    }
    else if (type == "AIPlayer 1" && numInstances == 2) {
        this->setName("AI 1");
    }
    else if (type == "AIPlayer 2" && numInstances == 1){
        this->setName("AI 2");
    }
    else if (type == "AIPlayer 2" && numInstances == 2){
        this->setName("AI 2");
    }
    bool validcords = false;
    for (const auto& ships: this->getShipInfo()) {
        do {
            this->setshipchoice(set_ship_choice(ships.first));
            if (get_valid_ship_pos(ships.first, ships.second)) {
                validcords = place_ship(ships.second, ships.first);
            }
        } while(!validcords);
        if (type == "AIPlayer 1" && numInstances == 1) {
            std::cout << "AI 1's Board" << std::endl;
            boardfunc.print_placement_board(game.players.at(0));
            std::cout << std::endl;
        }
        else if (type == "AIPlayer 1" && numInstances == 2) {
            std::cout << "AI 1's Board" << std::endl;
            boardfunc.print_placement_board(game.players.at(1));
            std::cout << std::endl;
        }
        else if (type == "AIPlayer 2" && numInstances == 1) {
            std::cout << "AI 2's Board" << std::endl;
            boardfunc.print_placement_board(game.players.at(0));
            std::cout << std::endl;
        }
        else if (type == "AIPlayer 2" && numInstances == 2){
            std::cout << "AI 2's Board" << std::endl;
            boardfunc.print_placement_board(game.players.at(1));
            std::cout << std::endl;
        }
    }
}
