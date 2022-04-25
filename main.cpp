#include <iostream>
#include "Game.h"
#include "Player.h"
#include "AiPlayer.h"
#include "CheatingAi.h"
#include "RandomAi.h"
#include "HumanPlayer.h"
#include "HuntAndDestroyAi.h"
#include <random>

bool check_seed(int argc, int& seed, char** argv);
void start_battleship(int playerchoice, char** argv);
void HumanvsHuman(char** argv);
void HumanvsAi(char** argv, int choice, std::string userchoice);
void AivsAi(char** argv, int choice, std::string userchoice);

int BattleShip::Player::numInstances = 0;

int main(int argc, char** argv) {
    int seed = 0;
    bool seedval;
    int playerchoice = 0;
    std::string player_choice;
    //  declaring variables needed to get player's choice and player's seed

    seedval = check_seed(argc, seed, argv);
    //  checks whether user passed in seed on command line and sets seed accordingly
    BattleShip::AiPlayer::assign_gen(seedval, seed);
    //  assigns our random number generator with given seed

    std::cout << "What type of game do you want to play?" << std::endl;
    std::cout << "1. Human vs Human" << std::endl;
    std::cout << "2. Human vs AI" << std::endl;
    std::cout << "3. AI vs AI" << std::endl;
    std::cout << "Your choice: ";
    getline(std::cin, player_choice);
    playerchoice = stoi(player_choice);
    //  prompts user to pick what type of game they want to play and gets their choice

    start_battleship(playerchoice, argv);
    //  starts battleship game with player's choice for type of game
    return 0;
}

bool check_seed(int argc, int& seed, char** argv) {
    //  checks whether user passed in a seed on command line
    if (argc == 3) {
        seed = std::stoi(argv[2]);
        return true;
    }
    else {
        seed = 0;
        return false;
    }
}
void HumanvsHuman(char** argv) {
    //  RUN HUMAN VS HUMAN
    BattleShip::Board boardfunc;
    std::unique_ptr<BattleShip::Player> Player1ptr;
    std::unique_ptr<BattleShip::Player> Player2ptr;
    BattleShip::Game the_game;
    BattleShip::HumanPlayer Player1;
    BattleShip::HumanPlayer Player2;
    //  declaring both human players and game instance

    Player1ptr = std::make_unique<BattleShip::HumanPlayer>(Player1);
    Player2ptr = std::make_unique<BattleShip::HumanPlayer>(Player2);
    //  setting both players to the inherted human player type

    Player1ptr->set_type("Player 1");
    Player2ptr->set_type("Player 2");
    //  setting both player's types

    the_game.get_info(argv[1]);
    //  calling get info in order to store num rows, cols, and all ships in config file
    the_game.set_player(Player1ptr);
    //  setting player 1 and player 2 in order to setup the game
    the_game.set_info(0);

    the_game.set_player(Player2ptr);
    //  setting player 1 and player 2 in order to setup the game
    the_game.set_info(1);
    //  sets each player's num rows, cols, and ship info

    the_game.set_up_game(the_game.players.at(0), boardfunc);
    the_game.set_up_game(the_game.players.at(1), boardfunc);
    the_game.start_game(the_game.players.at(0), the_game.players.at(1), boardfunc);
    // starts game between the players
}


void HumanvsAi(char** argv, int choice, std::string userchoice) {
    //  RUN HUMAN VS AI
    BattleShip::Board boardfunc;
    BattleShip::Game the_game;
    std::unique_ptr<BattleShip::Player> Player1AI;
    std::unique_ptr<BattleShip::Player> Player1Human;
    BattleShip::HumanPlayer Player1;
    //  declaring ai player, human player, and game instances

    the_game.get_info(argv[1]);
    //  gets info from configuration file about the game

    Player1Human = std::make_unique<BattleShip::HumanPlayer>(Player1);
    Player1Human->set_type("Player 1");
    //  sets human player to be of human player type and sets it to player 1

    Player1AI->countInstances();
    //  count number of instances we've made of player

    the_game.set_player(Player1Human);
    the_game.set_info(0);

    the_game.set_up_game(the_game.players.at(0), boardfunc);
    //  setting up the game and getting all ships for our human player

    std::cout << "What AI do you want?" << std::endl;
    std::cout << "1. Cheating AI" << std::endl;
    std::cout << "2. Random AI" << std::endl;
    std::cout << "3. Hunt Destroy AI" << std::endl;
    std::cout << "Your choice: ";
    getline(std::cin, userchoice);
    choice = stoi(userchoice);
    //  prompts user to which type of AI they want to play against

    if (choice == 1) {
        //  creates cheating ai and sets up its ships
        BattleShip::CheatingAi Player2;
        Player1AI = std::make_unique<BattleShip::CheatingAi>(Player2);
        Player1AI->set_type("AIPlayer 1");
        Player1AI->countInstances();
        the_game.set_player(Player1AI);
        the_game.set_info(1);

        the_game.players.at(1)->setrandomcoords();
        the_game.players.at(0)->insert_opponent_vector(the_game.players.at(1)->GetPlacementBoard());
        the_game.players.at(1)->insert_opponent_vector(the_game.players.at(0)->GetPlacementBoard());
    } else if (choice == 2) {
        //  creates random ai and sets up its ships
        BattleShip::RandomAi Player2;
        Player1AI = std::make_unique<BattleShip::RandomAi>(Player2);
        Player1AI->set_type("AIPlayer 1");
        Player1AI->countInstances();
        the_game.set_player(Player1AI);
        the_game.set_info(1);
        the_game.players.at(1)->setrandomcoords();
    } else {
        //  creates huntanddestroy ai and sets up its ships
        BattleShip::HuntAndDestroy Player2;
        Player1AI = std::make_unique<BattleShip::HuntAndDestroy>(Player2);
        Player1AI->set_type("AIPlayer 1");
        Player1AI->countInstances();
        the_game.set_player(Player1AI);
        the_game.set_info(1);
        the_game.players.at(1)->setrandomcoords();
    }
    the_game.set_up_game(the_game.players.at(1), boardfunc);

    the_game.start_game(the_game.players.at(0), the_game.players.at(1), boardfunc);
    //  starts game between player and ai
}


void AivsAi(char** argv, int choice, std::string userchoice) {
    //  RUN AI VS AI
    BattleShip::Board boardfunc;
    BattleShip::Game the_game;
    std::unique_ptr<BattleShip::Player> Player1AI;
    std::unique_ptr<BattleShip::Player> Player2AI;

    the_game.get_info(argv[1]);

    std::cout << "What AI do you want?" << std::endl;
    std::cout << "1. Cheating AI" << std::endl;
    std::cout << "2. Random AI" << std::endl;
    std::cout << "3. Hunt Destroy AI" << std::endl;
    std::cout << "Your choice: ";
    getline(std::cin, userchoice);
    choice = stoi(userchoice);

    //Ask user for which choice of Ai to play with Cheating, Random, and huntanddestroy
    //we create unique pointers with abstract classes to access child methods in setupgame.
    //We setup randomcoords which is the list of possible firing locations.
    //We count the number of instances to determine what type of player is necessary.
    if (choice == 1) {
        BattleShip::CheatingAi Player1;
        Player1AI = std::make_unique<BattleShip::CheatingAi>(Player1);
        Player1AI->set_type("AIPlayer 1");
        Player1AI->countInstances();
        the_game.set_player(Player1AI);
        the_game.set_info(0);
        the_game.players.at(0)->setrandomcoords();
        the_game.set_up_game(the_game.players.at(0), boardfunc);
    }
    else if (choice == 2) {
        BattleShip::RandomAi Player1;
        Player1AI = std::make_unique<BattleShip::RandomAi>(Player1);
        Player1AI->set_type("AIPlayer 1");
        Player1AI->countInstances();
        the_game.set_player(Player1AI);
        the_game.set_info(0);
        the_game.players.at(0)->setrandomcoords();
        the_game.set_up_game(the_game.players.at(0), boardfunc);
    }
    else {
        BattleShip::HuntAndDestroy Player1;
        Player1AI = std::make_unique<BattleShip::HuntAndDestroy>(Player1);
        Player1AI->set_type("AIPlayer 1");
        Player1AI->countInstances();
        the_game.set_player(Player1AI);
        the_game.set_info(0);
        the_game.players.at(0)->setrandomcoords();
        the_game.set_up_game(the_game.players.at(0), boardfunc);
    }

    std::cout << "What AI do you want?" << std::endl;
    std::cout << "1. Cheating AI" << std::endl;
    std::cout << "2. Random AI" << std::endl;
    std::cout << "3. Hunt Destroy AI" << std::endl;
    std::cout << "Your choice: ";
    getline(std::cin, userchoice);
    choice = stoi(userchoice);
    //  prompts user to which type of AI they want to play against

    if (choice == 1) {
        //  creates cheating ai and sets up its ships
        BattleShip::CheatingAi Player2;
        Player2AI = std::make_unique<BattleShip::CheatingAi>(Player2);
        Player2AI->set_type("AIPlayer 2");
        Player2AI->countInstances();
        the_game.set_player(Player2AI);
        the_game.set_info(1);
        the_game.players.at(1)->setrandomcoords();
        the_game.set_up_game(the_game.players.at(1), boardfunc);
        the_game.players.at(0)->insert_opponent_vector(the_game.players.at(1)->GetPlacementBoard());
        the_game.players.at(1)->insert_opponent_vector(the_game.players.at(0)->GetPlacementBoard());
    }
    else if (choice == 2) {
        //  creates random ai and sets up its ships
        BattleShip::RandomAi Player2;
        Player2AI = std::make_unique<BattleShip::RandomAi>(Player2);
        Player2AI->set_type("AIPlayer 2");
        Player2AI->countInstances();
        the_game.set_player(Player2AI);
        the_game.set_info(1);
        the_game.players.at(1)->setrandomcoords();
        the_game.set_up_game(the_game.players.at(1), boardfunc);
        the_game.players.at(0)->insert_opponent_vector(the_game.players.at(1)->GetPlacementBoard());
        the_game.players.at(1)->insert_opponent_vector(the_game.players.at(0)->GetPlacementBoard());
    }
    else {
        //  creates huntanddestroy ai and sets up its ships
        BattleShip::HuntAndDestroy Player2;
        Player2AI = std::make_unique<BattleShip::HuntAndDestroy>(Player2);
        Player2AI->set_type("AIPlayer 2");
        Player2AI->countInstances();
        the_game.set_player(Player2AI);
        the_game.set_info(1);
        the_game.players.at(1)->setrandomcoords();
        the_game.set_up_game(the_game.players.at(1), boardfunc);
        the_game.players.at(0)->insert_opponent_vector(the_game.players.at(1)->GetPlacementBoard());
        the_game.players.at(1)->insert_opponent_vector(the_game.players.at(0)->GetPlacementBoard());
    }
    the_game.start_game(the_game.players.at(0), the_game.players.at(1), boardfunc);
}


void start_battleship(int playerchoice, char** argv) {
    //  starts battleship games between players or ais
    std::string userchoice;
    int choice;
    if (playerchoice == 1) {
       HumanvsHuman(argv);
    }
    else if (playerchoice == 2) {
        HumanvsAi(argv, choice, userchoice);
    }
    else {
        AivsAi(argv, choice, userchoice);
    }
}
