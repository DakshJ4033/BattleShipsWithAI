cmake_minimum_required(VERSION 3.15.3)
project(BattleShip)

set(CMAKE_CXX_STANDARD 14)

add_executable(BattleShip main.cpp Game.h Game.cpp Player.h Player.cpp Board.h Board.cpp HumanPlayer.h HumanPlayer.cpp AiPlayer.cpp AiPlayer.h CheatingAi.h CheatingAi.cpp RandomAi.h RandomAi.cpp HuntAndDestroyAi.h HuntAndDestroyAi.cpp)