//
// Created by Beast PC on 5/7/2021.
//
#include "Board.h"
#include "Player.h"
#include <iostream>

int BattleShip::Board::getrows() {
    //  returns how many rows board has
    return rows;
}

int BattleShip::Board::getcols() {
    //  returns how many columns board has
    return cols;
}

void BattleShip::Board::print_player_status(std::unique_ptr<BattleShip::Player> &player) {
    //  prints player's firing and placement board
    std::cout << player->getName() << "'s Firing Board" << std::endl;
    this->print_firing_board(player);
    std::cout << std::endl;
    std::cout << std::endl;
    std::cout << player->getName() << "'s Placement Board" << std::endl;
    this->print_placement_board(player);
}

void BattleShip::Board::Initialize_Board(std::unique_ptr<BattleShip::Player>& player) {
    // initializes player's firing and placement boards
    Initialize_placement(player);
    Initialize_firing(player);
}

void BattleShip::Board::Initialize_placement(std::unique_ptr<BattleShip::Player> &player) {
    //  helps initialize player's placement board
    player->GetPlacementBoard().resize(player->getRows());
    for (int i = 0; i < player->GetPlacementBoard().size(); i++) {
        player->GetPlacementBoard()[i].resize(player->getCols());
    }
    for (int i = 0; i < player->getRows(); i++) {
        for (int j = 0; j < player->getCols(); j++) {
            player->GetPlacementBoard()[i][j] = '*';
        }
    }
    this->rows = player->getRows();
    this->cols = player->getCols();
}

void BattleShip::Board::Initialize_firing(std::unique_ptr<BattleShip::Player> &player) {
    //  helps initialize player's firing board
    player->GetFiringBoard().resize(player->getRows());
    for (int i = 0; i < player->GetFiringBoard().size(); i++) {
        player->GetFiringBoard()[i].resize(player->getCols());
    }

    for (int i = 0; i < player->getRows(); i++) {
        for (int j = 0; j < player->getCols(); j++) {
            player->GetFiringBoard()[i][j] = '*';
        }
    }
}

void BattleShip::Board::print_placement_board(std::unique_ptr<BattleShip::Player>& player) {
    //  prints player's placement board
    std::cout << "  ";
    if (player->getCols() >= 11) {
        print_big_placement_cols(player);
    }
    else if (player->getRows() >= 11) {
        print_big_placement_rows(player);
    }
    else {
        print_small_placement(player);
    }
}

void BattleShip::Board::print_firing_board(std::unique_ptr<BattleShip::Player> &player) {
    //  prints player's firing board
    std::cout << "  ";
    if (player->getCols() >= 11) {
        print_big_firing_cols(player);
    }
    else if (player->getRows() >= 11)  {
        print_big_firing_rows(player);
    }
    else {
        print_small_firing(player);
    }
}

void BattleShip::Board::print_big_placement_cols(std::unique_ptr<BattleShip::Player> &player) {
    //  prints big placement board due to large number of cols
    for (int i = 0; i < player->getCols(); i++) {
        std::cout << i << "  ";
    }
    std::cout << std::endl;
    for (int i = 0; i < player->getRows(); i++) {
        std::cout << i << " ";
        for (int j = 0; j < player->getCols(); j++) {
            std::cout << player->GetPlacementBoard()[i][j] << "  ";
        }
        std::cout << std::endl;
    }
}

void BattleShip::Board::print_big_placement_rows(std::unique_ptr<BattleShip::Player> &player) {
    //  prints big placement board due to large number of rows
    for (int i = 0; i < player->getCols(); i++) {
        std::cout << i << "  ";
    }
    std::cout << std::endl;
    for (int i = 0; i < player->getRows(); i++) {
        std::cout << i << " ";
        for (int j = 0; j < player->getCols(); j++) {
            std::cout << player->GetPlacementBoard()[i][j] << "  ";
        }
        std::cout << std::endl;
    }
}

void BattleShip::Board::print_small_placement(std::unique_ptr<BattleShip::Player> &player) {
    //  prints small placement board
    for (int i = 0; i < player->getCols(); i++) {
        std::cout << i << " ";
    }
    std::cout << std::endl;
    for (int i = 0; i < player->getRows(); i++) {
        std::cout << i << " ";
        for (int j = 0; j < player->getCols(); j++) {
            std::cout << player->GetPlacementBoard()[i][j] << " ";
        }
        std::cout << std::endl;
    }
}

void BattleShip::Board::print_big_firing_cols(std::unique_ptr<BattleShip::Player> &player) {
    // prints big firing board due to large number of cols
    for (int i = 0; i < player->getCols(); i++) {
        std::cout << i << "  ";
    }
    std::cout << std::endl;
    for (int i = 0; i < player->getRows(); i++) {
        std::cout << i << " ";
        for (int j = 0; j < player->getCols(); j++) {
            std::cout << player->GetFiringBoard()[i][j] << "  ";
        }
        std::cout << std::endl;
    }
}

void BattleShip::Board::print_big_firing_rows(std::unique_ptr<BattleShip::Player> &player) {
    // prints big firing board due to large number of rows
    for (int i = 0; i < player->getCols(); i++) {
        std::cout << i << "  ";
    }
    std::cout << std::endl;
    for (int i = 0; i < player->getRows(); i++) {
        std::cout << i << " ";
        for (int j = 0; j < player->getCols(); j++) {
            std::cout << player->GetFiringBoard()[i][j] << "  ";
        }
        std::cout << std::endl;
    }
}

void BattleShip::Board::print_small_firing(std::unique_ptr<BattleShip::Player> &player) {
    //  prints small firing board
    for (int i = 0; i < player->getCols(); i++) {
        std::cout << i << " ";
    }
    std::cout << std::endl;
    for (int i = 0; i < player->getRows(); i++) {
        std::cout << i << " ";
        for (int j = 0; j < player->getCols(); j++) {
            std::cout << player->GetFiringBoard()[i][j] << " ";
        }
        std::cout << std::endl;
    }
}
