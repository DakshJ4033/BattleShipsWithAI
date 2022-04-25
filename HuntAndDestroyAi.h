//
// Created by Beast PC on 5/22/2021.
//

#ifndef BATTLESHIP_HUNTANDDESTROYAI_H
#define BATTLESHIP_HUNTANDDESTROYAI_H

#include "RandomAi.h"

namespace BattleShip {
    class Board;
    class HuntAndDestroy : public RandomAi {
    public:
        void insertcoords();
        virtual void get_valid_firing_placement(Board& theboard, Game& game);
        virtual void setrandomcoords() override;
    private:
        std::vector<std::pair<int, int>> randomcoords;
        bool huntmode = true;
        std::vector<std::pair<int, int>> huntdestroycoords;
    };
}

#endif //BATTLESHIP_HUNTANDDESTROYAI_H
