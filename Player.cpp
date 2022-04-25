//
// Created by Beast PC on 5/7/2021.
//
#include "Player.h"
#include <iostream>
#include <sstream>
#include <map>

void BattleShip::Player::countInstances() {
    numInstances++;
}

void BattleShip::Player::set_type(std::string playertype) {
    this->type = playertype;
}

std::map<char, int>& BattleShip::Player::getShipInfo() {
    return ship_info;
}

void BattleShip::Player::setName(std::string name) {
    this->PlayerName = name;
}

void BattleShip::Player::SetRows(int num_rows) {
    this->num_rows = num_rows;
}

void BattleShip::Player::SetCols(int num_cols) {
    this->num_cols = num_cols;
}

int BattleShip::Player::getRows() {
    return num_rows;
}

int BattleShip::Player::getCols() {
    return num_cols;
}

int BattleShip::Player::retrievefiringcol() {
    return fireplacementcol;
}

int BattleShip::Player::retrievefiringrow() {
    return fireplacementrow;
}

void BattleShip::Player::SetShipInfo(std::map<char, int> ship_info) {
    this->ship_info = ship_info;
}

std::vector<std::vector<char>>& BattleShip::Player::GetPlacementBoard() {
    return PlayerPlacementBoard;
}

std::vector<std::vector<char>>& BattleShip::Player::GetFiringBoard() {
    return PlayerFiringBoard;
}

char BattleShip::Player::get_shipchoicedestroy() {
    return shipchoicedestroy;
}

int BattleShip::Player::retrieveshipsum() {
    return totalsumofships;
}

std::string BattleShip::Player::getName() {
    return PlayerName;
}

std::string BattleShip::Player::retrieveshipchoice() {
    return shipchoice;
}

std::vector<std::vector<char>>& BattleShip::Player::RetrieveOpponentBoard() {
    return OpponentPlacementBoard;
}

void BattleShip::Player::setshipchoice(std::string symbol) {
    this->shipchoice = symbol;
}

void BattleShip::Player::setshipcordrow(int row) {
    //  shipcoordrow setter
    this->shipcoordrow = row;
}

void BattleShip::Player::setshipcordcol(int col) {
    //  shipcoordcol setter
    shipcoordcol = col;
}

void BattleShip::Player::setfirecordrow(int row) {
    //  shipfirecoordrow setter
    fireplacementrow = row;
}

void BattleShip::Player::setfirecordcol(int col) {
    //  shipfirecoordcol setter
    fireplacementcol = col;
}

void BattleShip::Player::insert_opponent_vector(std::vector<std::vector<char>>& opponentvec) {
    //  sets opponent placement board to be opponentvec
    OpponentPlacementBoard = opponentvec;
}

//We add up all the lengths of the ships and add them to the total sum to determine whether or not all the player's ships are destroyed.
void BattleShip::Player::set_total_sum_of_ships() {
    totalsumofships = 0;
    for (const auto& ships : ship_info) {
        totalsumofships += ships.second;
    }
}

//We check out of bounds and if we've fired into the same spot already
bool BattleShip::Player::validfiringmovecord() {

    if (this->fireplacementrow < 0 || this->fireplacementrow > this->num_rows - 1) {
        return false;
    } else if (this->fireplacementcol < 0 || this->fireplacementcol > this->num_cols - 1) {
        return false;
    }
    else if (GetFiringBoard()[fireplacementrow][fireplacementcol] == 'O' || GetFiringBoard()[fireplacementrow][fireplacementcol] == 'X') {
        return false;
    }
    return true;
}

//for each ship in the playing field, we counted the number of xs from obtaining the ship coordinates and if the number of xs is equivalent
//to the length of the ship, it's a destroyed ship.
bool BattleShip::Player::shipsdestroyed() {
    int num_destroyed_ships;
    int xcounter = 0;
    int xcoord;
    int ycoord;
    for (const auto& ships : coordinfo) {
        for (const auto& item : coordinfo.at(ships.first)) {
            xcoord = item.first;
            ycoord = item.second;
            if (GetPlacementBoard()[xcoord][ycoord] == 'X') {
                ++xcounter;
            }
        }
        if (xcounter == ship_info.at(ships.first)) {
            this->shipchoicedestroy = ships.first;
            coordinfo.erase(ships.first);
            return true;
        }
        xcounter = 0;
    }
    return false;
}

//We first check if there's overlap with the ship placement and return false when it is.
//Next, we place the ships and push back each of the coordinates into the map so we can
//determine if the battleship has been destroyed yet.
bool BattleShip::Player::place_horizontal(int ship_length, char shipsymbol) {
    for (int i = 0; i < ship_length; i++) {
        if (GetPlacementBoard()[shipcoordrow][shipcoordcol + i] != '*') {
            return false;
        }
    }
    for (int i = 0; i < ship_length; i++) {
        GetPlacementBoard()[shipcoordrow][shipcoordcol + i] = shipsymbol;
        if (coordinfo.count(shipsymbol) > 0) {
            coordinfo.at(shipsymbol).push_back(std::make_pair(shipcoordrow, shipcoordcol + i));
        }
        else {
            coordinfo.insert({shipsymbol, {std::make_pair(shipcoordrow, shipcoordcol + i)}});
        }
    }
    return true;
}

//We first check if there's overlap with the ship placement and return false when it is.
//Next, we place the ships and push back each of the coordinates into the map so we can
//determine if the battleship has been destroyed yet. This is the same, but vertically.
bool BattleShip::Player::place_vertical(int ship_length, char shipsymbol) {
    for (int i = 0; i < ship_length; i++) {
        if (GetPlacementBoard()[shipcoordrow + i][shipcoordcol] != '*') {
            return false;
        }
    }
    for (int i = 0; i < ship_length; i++) {
        GetPlacementBoard()[shipcoordrow + i][shipcoordcol] = shipsymbol;
        if (coordinfo.count(shipsymbol) > 0) {
            coordinfo.at(shipsymbol).push_back(std::make_pair(shipcoordrow + i, shipcoordcol));
        }
        else {
            coordinfo.insert({shipsymbol, {std::make_pair(shipcoordrow + i, shipcoordcol)}});
        }
    }
    return true;
}

//If the ship coordinates are too big or too small for the board, we return false.
//We return true otherwise. (horizontally)
bool BattleShip::Player::check_horizontal(int ship_length) {
    if (shipcoordrow < 0 || shipcoordcol < 0) {
        return false;
    }
    else if (shipcoordrow > num_rows - 1 || shipcoordcol > num_cols - 1) {
        return false;
    }
    else if (shipcoordcol + ship_length > num_cols) {
        return false;
    }
    else {
        return true;
    }
}

//If the ship coordinates are too big or too small for the board, we return false.
//We return true otherwise. (vertically)
bool BattleShip::Player::check_vertical(int ship_length) {
    if (shipcoordrow < 0 || shipcoordcol < 0) {
        return false;
    }
    else if (shipcoordrow > num_rows - 1 || shipcoordcol > num_cols - 1) {
        return false;
    }
    else if (shipcoordrow + ship_length > num_rows) {
        return false;
    }
    else {
        return true;
    }
}
