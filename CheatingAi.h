//
// Created by Beast PC on 5/22/2021.
//

#ifndef BATTLESHIP_CHEATINGAI_H
#define BATTLESHIP_CHEATINGAI_H

#include "AiPlayer.h"

namespace BattleShip {
    class CheatingAi : public AiPlayer {
    public:
        virtual void get_valid_firing_placement(Board& theboard, Game& game);
        virtual void setrandomcoords() override;
    private:
        std::vector<std::pair<int, int>> randomcoords;
    };
}

#endif //BATTLESHIP_CHEATINGAI_H
