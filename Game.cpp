//
// Created by Beast PC on 5/7/2021.
//

#include "Game.h"
#include "Player.h"
#include <ostream>
#include <fstream>
#include <memory>
#include <sstream>

void BattleShip::Game::get_info(std::string filename) {
    //  gets all information from configuration file and inserts that info in Game class variables
    std::ifstream File;
    int input;
    char symbol;

    File.open(filename);
    for (int i = 0; i < 3; i++) {
        File >> input;
        boardInfo.push_back(input);
    }
    while (!File.eof()) {
        File >> symbol;
        File >> input;
        ship_info.insert(std::pair<char,int>(symbol, input));
    }
}

void BattleShip::Game::set_player(std::unique_ptr<BattleShip::Player>& Player) {
    //  adds unique pointers to players vector
    this->players.push_back(move(Player));
}

void BattleShip::Game::set_info(int i) {
    //  sets num rows, num cols, and ship info for each player in unique pointer vector
    players.at(i)->SetRows(boardInfo.at(0));
    players.at(i)->SetCols(boardInfo.at(1));
    players.at(i)->SetShipInfo(ship_info);

//    players.at(1)->SetRows(boardInfo.at(0));
//    players.at(1)->SetCols(boardInfo.at(1));
//    players.at(1)->SetShipInfo(ship_info);
}

std::string BattleShip::Game::get_valid_name(std::string prompt) {
    //  gets valid name for each player
    std::string line;
    while (true) {
        std::cout << prompt;
        getline(std::cin, line); //grabs the entire line
        std::stringstream line2parse(line);
        std::string name;
        line2parse >> name;
        if (line2parse) { //if I was able to read the number
            std::string what_is_left;
            line2parse >> what_is_left;
            if (!line2parse) { //if there is nothing left we will fail to read it
                return name;
            }
        }
    }
}

bool BattleShip::Game::fire_player1(std::unique_ptr<BattleShip::Player>& Player1, std::unique_ptr<BattleShip::Player>& Player2) {
    //  firing function for player 1, makes sure to check for overlaps and sets its firing and the other's placement board
    //  with correct firing symbols
    if (Player2->GetPlacementBoard()[Player1->retrievefiringrow()][Player1->retrievefiringcol()] != '*'
        and Player2->GetPlacementBoard()[Player1->retrievefiringrow()][Player1->retrievefiringcol()] != 'X' and
        Player2->GetPlacementBoard()[Player1->retrievefiringrow()][Player1->retrievefiringcol()] != 'O') {
        this->currSymbol = Player2->GetPlacementBoard()[Player1->retrievefiringrow()][Player1->retrievefiringcol()];
        Player1->GetFiringBoard()[Player1->retrievefiringrow()][Player1->retrievefiringcol()] = 'X';
        Player2->GetPlacementBoard()[Player1->retrievefiringrow()][Player1->retrievefiringcol()] = 'X';
        return true;
    } else {
        this->currSymbol = Player2->GetPlacementBoard()[Player1->retrievefiringrow()][Player1->retrievefiringcol()];
        Player1->GetFiringBoard()[Player1->retrievefiringrow()][Player1->retrievefiringcol()] = 'O';
        Player2->GetPlacementBoard()[Player1->retrievefiringrow()][Player1->retrievefiringcol()] = 'O';
        return false;
    }
}

bool BattleShip::Game::fire_player2(std::unique_ptr<BattleShip::Player>& Player1, std::unique_ptr<BattleShip::Player>& Player2) {
    //  firing function for player 2, makes sure to check for overlaps and sets its firing and the other's placement board
    //  with correct firing symbols
    if (Player1->GetPlacementBoard()[Player2->retrievefiringrow()][Player2->retrievefiringcol()] != '*'
        and Player1->GetPlacementBoard()[Player2->retrievefiringrow()][Player2->retrievefiringcol()] != 'X' and
        Player1->GetPlacementBoard()[Player2->retrievefiringrow()][Player2->retrievefiringcol()] != 'O') {
        this->currSymbol = Player1->GetPlacementBoard()[Player2->retrievefiringrow()][Player2->retrievefiringcol()];
        Player2->GetFiringBoard()[Player2->retrievefiringrow()][Player2->retrievefiringcol()] = 'X';
        Player1->GetPlacementBoard()[Player2->retrievefiringrow()][Player2->retrievefiringcol()] = 'X';
        return true;
    } else {
        this->currSymbol = Player1->GetPlacementBoard()[Player2->retrievefiringrow()][Player2->retrievefiringcol()];
        Player2->GetFiringBoard()[Player2->retrievefiringrow()][Player2->retrievefiringcol()] = 'O';
        Player1->GetPlacementBoard()[Player2->retrievefiringrow()][Player2->retrievefiringcol()] = 'O';
        return false;
    }
}

bool BattleShip::Game::make_firingmove(std::unique_ptr<BattleShip::Player>& Player1, std::unique_ptr<BattleShip::Player>& Player2, int playerturn) {
    //  makes firing move depending on which turn it is - player 1 or player 2
    bool check_fire;
    if (playerturn == 1) {
        check_fire = fire_player1(Player1, Player2);
        players.at(0)->insert_opponent_vector(players.at(1)->GetPlacementBoard());
        return check_fire;
    } else if (playerturn == 2) {
        check_fire = fire_player2(Player1, Player2);
        players.at(1)->insert_opponent_vector(players.at(0)->GetPlacementBoard());
        return check_fire;
    }
    return false;
}

void BattleShip::Game::set_up_game(std::unique_ptr<BattleShip::Player> &Player1, Board &theboard) {
    //  initializes boards for both player 1 and player 2
    //  sets the sum of length of ships in order to check for win later
    //  makes the inital call to setupbattleships to "start" the game
    theboard.Initialize_Board(Player1);
    Player1->set_total_sum_of_ships();
    if (Player1->type == "Player 1") {
        Player1->SetupBattleShips(*this, "Player 1 please enter your name: ", theboard);
    }
    else {
        Player1->SetupBattleShips(*this, "Player 2 please enter your name: ", theboard);
    }
}

void BattleShip::Game::fire_opponent_ship_1(std::unique_ptr<BattleShip::Player>& Player1, std::unique_ptr<BattleShip::Player>& Player2, Board& theboard, int playerturn) {
    //  if player 1 was able to get a hit, we notify player 1 and also check
    //  whether they fully destroyed the opponents board
    if (make_firingmove(Player1, Player2, 1)) {
        theboard.print_player_status(Player1);
        std::cout << Player1->getName() << " hit" << " " << Player2->getName() << "'s " <<
                  currSymbol << "!";
        std::cout << std::endl;
        if (Player2->shipsdestroyed()) {
            std::cout << Player1->getName() << " destroyed " << Player2->getName() << "'s " << Player2->get_shipchoicedestroy() << "!" << std::endl;
            std::cout << std::endl;
        } else {
            std::cout << std::endl;
        }
    } else {
        theboard.print_player_status(Player1);
        std::cout << "Missed." << std::endl;
        std::cout << std::endl;
    }
}

void BattleShip::Game::fire_opponent_ship_2(std::unique_ptr<BattleShip::Player>& Player1, std::unique_ptr<BattleShip::Player>& Player2, Board& theboard, int playerturn) {
    //  if player 2 was able to get a hit, we notify player 2 and also check
    //  whether they fully destroyed the opponents board
    if (make_firingmove(Player1, Player2, 2)) {
        theboard.print_player_status(Player2);
        std::cout << Player2->getName() << " hit" << " " << Player1->getName() << "'s " <<
                  currSymbol << "!";
        std::cout << std::endl;
        if (Player1->shipsdestroyed()) {
            std::cout << Player2->getName() << " destroyed " << Player1->getName() << "'s " << Player1->get_shipchoicedestroy() << "!" << std::endl;
            std::cout << std::endl;
        } else {
            std::cout << std::endl;
        }
    } else {
        theboard.print_player_status(Player2);
        std::cout << "Missed." << std::endl;
        std::cout << std::endl;
    }
}

void BattleShip::Game::start_game(std::unique_ptr<BattleShip::Player>& Player1, std::unique_ptr<BattleShip::Player>& Player2, Board& theboard) {
    //  starts the battleship game between the players - setting up ships, printing each player's boards
    //  getting firing placement, checking that firing placement, and finally checking whether someone won
    //  or not
    int playerturn = 1;
    while (is_game_over(Player1) && is_game_over(Player2)) {
        if (playerturn == 1) {
            if (players.at(0)->type == "Player 1") {
                theboard.print_player_status(Player1);
            }
            Player1->get_valid_firing_placement(theboard, *this);
            fire_opponent_ship_1(Player1, Player2, theboard, 1);
            playerturn = 2;
        }
        else if (playerturn == 2) {
            if (players.at(1)->type == "Player 2") {
                theboard.print_player_status(Player2);
            }
            Player2->get_valid_firing_placement(theboard, *this);
            fire_opponent_ship_2(Player1, Player2, theboard, 2);
            playerturn = 1;
        }
    }
    if (is_game_over(Player1)) {
        std::cout << Player1->getName() << " won the game!" << std::endl;
    } else {
        std::cout << Player2->getName() << " won the game!" << std::endl;
    }
}

bool BattleShip::Game::is_game_over(std::unique_ptr<BattleShip::Player>& player) {
    //  checks whether game is over by checking if a player has destroyed all opponent ships on the board
    int sumships = player->retrieveshipsum();
    int xcounter = 0;
    for (int i = 0; i < player->getRows(); i++) {
        for (int j = 0; j < player->getCols(); j++) {
            if (player->GetPlacementBoard()[i][j] == 'X') {
                    ++xcounter;
            }
        }
    }
    if (xcounter == sumships) {
        return false;
    } else {
        return true;
    }
}
