//
// Created by Beast PC on 5/21/2021.
//

#ifndef BATTLESHIP_AIPLAYER_H
#define BATTLESHIP_AIPLAYER_H
#include <random>
#include "Player.h"

namespace BattleShip {
    class Board;
    class AiPlayer : public Player {
    public:
        virtual bool place_ship(int ship_length, char shipsymbol) override;
        virtual bool check_valid_pos(int ship_length) override;
        virtual bool get_valid_ship_pos(char shipsymbol, int length) override;
        virtual void get_valid_firing_placement(Board& theboard, Game& game) = 0;
        virtual void SetupBattleShips(Game& game, std::string prompt, Board& boardfunc) override;
        virtual std::string set_ship_choice(char shipSymbol) override;
        int generatehorizontalvertical(std::mt19937& thegenerator);
        int generatecol(std::mt19937& thegenerator, int length);
        int generaterow(std::mt19937& thegenerator, int length);
        std::string get_AI_orientation();
        static void assign_gen(bool seedval, int seed);
        std::mt19937& getgenerator();
    protected:
        static std::mt19937 gen;
    private:
        std::string shiporientation;
    };
}

#endif //BATTLESHIP_AIPLAYER_H
