//
// Created by Beast PC on 5/22/2021.
//

#ifndef BATTLESHIP_RANDOMAI_H
#define BATTLESHIP_RANDOMAI_H
#include "AiPlayer.h"
#include <iterator>

namespace BattleShip {
    class Board;
    class RandomAi : public AiPlayer {
    public:
        virtual void setrandomcoords() override;
        virtual void get_valid_firing_placement(Board& theboard, Game& game);
        // template<typename RandomNumberGenerator>

        int getRandomInt(int min, int max, std::mt19937& generator) {
            std::uniform_int_distribution<int> dist(min, max);
            int random_num = dist(generator);
            return random_num;
        }
//        template<typename Container, typename RandomNumberGenerator>
//        typename Container::iterator getRandomIteratorToElement(Container& container, RandomNumberGenerator& rng) {
//            auto elementPos = getRandomInt(0, container.size() - 1, gen);
//            auto itr = container.begin();
//            std::advance(itr, elementPos);
//            return itr;
//        }
    private:
        std::vector<std::pair<int, int>> randomcoords;
    };
}

#endif //BATTLESHIP_RANDOMAI_H
