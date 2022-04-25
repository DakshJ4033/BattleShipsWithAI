//
// Created by Beast PC on 5/22/2021.
//
#include "RandomAi.h"

void BattleShip::RandomAi::get_valid_firing_placement(Board& theboard, Game& game) {
    //  gets random firing position thats valid
    int randomindex = getRandomInt(0, randomcoords.size() - 1, gen);
    setfirecordrow(randomcoords.at(randomindex).first);
    setfirecordcol(randomcoords.at(randomindex).second);
    randomcoords.erase(randomcoords.begin() + randomindex);
}

void BattleShip::RandomAi::setrandomcoords() {
    //  sets big vector with all possible positions on the board
    for (int i = 0; i < getRows(); i++) {
        for (int j = 0; j < getCols(); j++) {
            randomcoords.emplace_back(std::make_pair(i, j));
        }
    }
}
