//
// Created by Beast PC on 5/21/2021.
//

#ifndef BATTLESHIP_HUMANPLAYER_H
#define BATTLESHIP_HUMANPLAYER_H

#include "Player.h"

namespace BattleShip {
    class Board;
    class HumanPlayer : public Player {
    public:
        virtual void setrandomcoords() override;
        virtual bool place_ship(int ship_length, char shipsymbol) override;
        virtual bool check_valid_pos(int ship_length) override;
        virtual bool get_valid_ship_pos(char shipSymbol, int length) override;
        virtual void get_valid_firing_placement(Board& theboard, Game& game) override;
        virtual std::string set_ship_choice(char shipSymbol) override;
        std::string get_valid_ship(const std::string &prompt, char shipSymbol);
        virtual void SetupBattleShips(Game& game, std::string prompt, Board& boardfunc) override;
    };
}

#endif //BATTLESHIP_HUMANPLAYER_H
