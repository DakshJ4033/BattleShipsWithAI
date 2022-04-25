//
// Created by Beast PC on 5/7/2021.
//

#ifndef BATTLESHIP_GAME_H
#define BATTLESHIP_GAME_H
#include <map>
#include <vector>
#include <memory>
#include <string>
#include "Board.h"

namespace BattleShip {
    class Player;
    class Game {
    public:
        //  declaring all functions in the player class
        void get_info(std::string filename);
        void set_player(std::unique_ptr<BattleShip::Player>& Player);
        void set_info(int i);
        void set_up_game(std::unique_ptr<BattleShip::Player>& Player1, BattleShip::Board& theboard);
        bool fire_player1(std::unique_ptr<BattleShip::Player>& Player1, std::unique_ptr<BattleShip::Player>& Player2);
        bool fire_player2(std::unique_ptr<BattleShip::Player>& Player1, std::unique_ptr<BattleShip::Player>& Player2);
        void fire_opponent_ship_1(std::unique_ptr<BattleShip::Player>& Player1, std::unique_ptr<BattleShip::Player>& Player2, Board& theboard, int playerturn);
        void fire_opponent_ship_2(std::unique_ptr<BattleShip::Player>& Player1, std::unique_ptr<BattleShip::Player>& Player2, Board& theboard, int playerturn);
        std::string get_valid_name(std::string prompt);
        void start_game(std::unique_ptr<BattleShip::Player>& Player1, std::unique_ptr<BattleShip::Player>& Player2, Board& theboard);
        bool make_firingmove(std::unique_ptr<BattleShip::Player>& Player1, std::unique_ptr<BattleShip::Player>& Player2, int playerturn);
        bool is_game_over(std::unique_ptr<BattleShip::Player>& player);

        std::vector<std::unique_ptr<Player>> players;
    private:
        //  all private members that shouldn't be changed
        std::vector<int> boardInfo;
        std::map<char, int> ship_info;
        char currSymbol;
    };
}

#endif //BATTLESHIP_GAME_H
