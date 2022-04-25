//
// Created by Beast PC on 5/22/2021.
//
#include "CheatingAi.h"

void BattleShip::CheatingAi::get_valid_firing_placement(Board& theboard, Game& game) {
    //  goes through entire board and stops as soon as it sees a valid firing position and then sets
    //  firecoordrow and firecoordcol to that position
    for (int i = 0; i < theboard.getrows(); i++) {
        for (int j = 0; j < theboard.getcols(); j++) {
            if (RetrieveOpponentBoard()[i][j] != '*' && RetrieveOpponentBoard()[i][j] != 'X'
            && RetrieveOpponentBoard()[i][j] != 'O') {
                this->setfirecordrow(i);
                this->setfirecordcol(j);
                return;
            }
        }
    }
}

void BattleShip::CheatingAi::setrandomcoords() {
    //  sets big vector for every position on the board
    for (int i = 0; i < getRows(); i++) {
        for (int j = 0; j < getCols(); j++) {
            randomcoords.emplace_back(std::make_pair(i, j));
        }
    }
}
