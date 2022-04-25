//
// Created by Beast PC on 5/7/2021.
//

#ifndef BATTLESHIP_BOARD_H
#define BATTLESHIP_BOARD_H
#include <memory>

namespace BattleShip {
    class Player;
    class Board {
    public:
        //  declaring all functions needed in Board class
        void Initialize_Board(std::unique_ptr<BattleShip::Player> &player);
        void Initialize_placement(std::unique_ptr<BattleShip::Player> &player);
        void Initialize_firing(std::unique_ptr<BattleShip::Player> &player);
        void print_placement_board(std::unique_ptr<BattleShip::Player>& player);
        void print_firing_board(std::unique_ptr<BattleShip::Player>& player);
        void print_big_firing_cols(std::unique_ptr<BattleShip::Player> &player);
        void print_big_firing_rows(std::unique_ptr<BattleShip::Player> &player);
        void print_small_firing(std::unique_ptr<BattleShip::Player> &player);
        void print_big_placement_cols(std::unique_ptr<BattleShip::Player> &player);
        void print_big_placement_rows(std::unique_ptr<BattleShip::Player> &player);
        void print_small_placement(std::unique_ptr<BattleShip::Player> &player);
        void print_player_status(std::unique_ptr<BattleShip::Player> &player);
        int getrows();
        int getcols();
    private:
        int rows;
        int cols;
    };
}

#endif //BATTLESHIP_BOARD_H
