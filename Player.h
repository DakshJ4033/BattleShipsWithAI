//
// Created by Beast PC on 5/7/2021.
//
#ifndef BATTLESHIP_PLAYER_H
#define BATTLESHIP_PLAYER_H
#include <string>
#include <vector>
#include <map>
#include "Board.h"
#include "Game.h"
#include <iostream>

namespace BattleShip {
    class Player {
        public:
            void countInstances();
            virtual void setrandomcoords() = 0;
            virtual bool place_ship(int ship_length, char shipsymbol) = 0;
            virtual bool check_valid_pos(int ship_length) = 0;
            virtual bool get_valid_ship_pos(char shipSymbol, int length) = 0;
            virtual void get_valid_firing_placement(Board& theboard, Game& game) = 0;
            virtual void SetupBattleShips(Game& game, std::string prompt, Board& boardfunc) = 0;
            virtual std::string set_ship_choice(char shipSymbol) = 0;
            bool place_horizontal(int ship_length, char shipsymbol);
            bool place_vertical(int ship_length, char shipsymbol);
            bool check_horizontal(int ship_length);
            bool check_vertical(int ship_length);
            bool shipsdestroyed();
            void set_total_sum_of_ships();
            void SetShipInfo(std::map<char, int> ship_info);
            std::vector<std::vector<char>>& GetPlacementBoard();
            std::vector<std::vector<char>>& GetFiringBoard();
            void insert_opponent_vector(std::vector<std::vector<char>>& opponentvec);
            void set_type(std::string playertype);
            void SetRows(int num_rows);
            void SetCols(int num_cols);
            int getRows();
            int getCols();
            std::string retrieveshipchoice();
            char get_shipchoicedestroy();
            int retrieveshipsum();
            int retrievefiringrow();
            int retrievefiringcol();
            std::vector<std::vector<char>>& RetrieveOpponentBoard();
            void setshipcordrow(int row);
            void setshipcordcol(int col);
            void setfirecordrow(int row);
            void setfirecordcol(int col);
            void setshipchoice(std::string symbol);
            std::string getName();
            bool validfiringmovecord();
            void setName(std::string name);
            std::map<char, int>& getShipInfo();
            std::string PlayerName;
            std::string type;
    protected:
            static int numInstances;
        private:

            std::string shipchoice;
            char shipchoicedestroy = 'Z';
            int totalsumofships = 0;
            int num_rows;
            int num_cols;
            int shipcoordrow;
            int shipcoordcol;
            int fireplacementrow;
            int fireplacementcol;
            int counterX = 0;
            std::map<char, int> ship_info;
            std::map<char, std::vector<std::pair<int, int>>> coordinfo;
            std::vector<std::vector<char>> PlayerPlacementBoard;
            std::vector<std::vector<char>> PlayerFiringBoard;
            std::vector<std::vector<char>> OpponentPlacementBoard;
    };
}

#endif //BATTLESHIP_PLAYER_H
