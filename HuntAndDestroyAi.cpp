//
// Created by Beast PC on 5/22/2021.
//

#include "HuntAndDestroyAi.h"
#include <algorithm>

void BattleShip::HuntAndDestroy::setrandomcoords() {
    //  sets big vector to get every single position on our board
    for (int i = 0; i < getRows(); i++) {
        for (int j = 0; j < getCols(); j++) {
            randomcoords.emplace_back(std::make_pair(i, j));
        }
    }
}

void BattleShip::HuntAndDestroy::insertcoords() {
    //Once we hit a spot on the opponent's that is a ship piece, for the hunt and destroy ai, we should be pushing
    //all of the directions of the rows and cols that are left, up, right and down to the huntdestroycoords.
    auto left = std::make_pair(retrievefiringrow(), retrievefiringcol() - 1);
    if ((std::find(randomcoords.begin(), randomcoords.end(), left) != randomcoords.end())
    && !(std::find(huntdestroycoords.begin(), huntdestroycoords.end(), left) != huntdestroycoords.end())) {
        huntdestroycoords.push_back(left);
    }
    auto up = std::make_pair(retrievefiringrow() - 1, retrievefiringcol());
    if ((std::find(randomcoords.begin(), randomcoords.end(),up) != randomcoords.end()) &&
    !(std::find(huntdestroycoords.begin(), huntdestroycoords.end(), up) != huntdestroycoords.end())) {
        huntdestroycoords.push_back(up);
    }
    auto right = std::make_pair(retrievefiringrow(), retrievefiringcol() + 1);
    if ((std::find(randomcoords.begin(), randomcoords.end(), right) != randomcoords.end()) &&
    !(std::find(huntdestroycoords.begin(), huntdestroycoords.end(), right) != huntdestroycoords.end())) {
        huntdestroycoords.push_back(right);
    }
    auto down = std::make_pair(retrievefiringrow() + 1, retrievefiringcol());
    if ((std::find(randomcoords.begin(), randomcoords.end(), down) != randomcoords.end()) &&
    !(std::find(huntdestroycoords.begin(), huntdestroycoords.end(), down) != huntdestroycoords.end())) {
        huntdestroycoords.push_back(down);
    }
}

void BattleShip::HuntAndDestroy::get_valid_firing_placement(Board& theboard, Game& game) {
    if (huntmode) {
        //If it's hunt mode, we get a random index from the list of possible firing locations in randomcoords
        //We set the firing row and column to be the the first part of the pair and second part of the pair.
        int randomindex = getRandomInt(0, randomcoords.size() - 1, gen);
        setfirecordrow(randomcoords.at(randomindex).first);
        setfirecordcol(randomcoords.at(randomindex).second);
        randomcoords.erase(randomcoords.begin() + randomindex);
        //Everytime we make a move we erase the from the list of possible firing locations
        //We set the huntmode to be false whenever we find a hit on the opponents.
        if (RetrieveOpponentBoard()[retrievefiringrow()][retrievefiringcol()] != '*' &&
                RetrieveOpponentBoard()[retrievefiringrow()][retrievefiringcol()] != 'X' &&
                RetrieveOpponentBoard()[retrievefiringrow()][retrievefiringcol()] != 'O') {
            insertcoords();
            huntmode = false;
        }
    } else {
        //We set the firing rows and columns to be from the pair of coordinates in the huntdestroy coords list.
        setfirecordrow(huntdestroycoords.at(0).first);
        setfirecordcol(huntdestroycoords.at(0).second);
        auto itr = std::find(randomcoords.begin(), randomcoords.end(), huntdestroycoords.at(0));
        randomcoords.erase(itr);
        //We use an iterator to find the current hunt destroy coords in side of the list of possible firing locations
        //And we erase it from the main vector of locations.
        if (RetrieveOpponentBoard()[retrievefiringrow()][retrievefiringcol()] != '*' &&
                RetrieveOpponentBoard()[retrievefiringrow()][retrievefiringcol()] != 'X' &&
                RetrieveOpponentBoard()[retrievefiringrow()][retrievefiringcol()] != 'O') {
            insertcoords();
        }
        huntdestroycoords.erase(huntdestroycoords.begin());
        if (huntdestroycoords.empty()) {
            huntmode = true;
        }
        //If there are no more coordinates to fire at in huntdestroycoords, then we can switch huntmode to be true as we've exhausted all the
        //possible positions to fire at from left up right and down from a hit.
    }
}
