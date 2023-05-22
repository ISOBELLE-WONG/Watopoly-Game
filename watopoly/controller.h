#ifndef __CONTROLLER_H__
#define __CONTROLLER_H__


#include <algorithm>
#include <chrono>
#include <memory>
#include <random>
#include <string>
#include <vector>
#include <time.h>
#include <fstream>
#include <sstream>
#include <iostream>
#include "grid.h"
#include "player.h"
#include "property.h"
#include "ownable.h"


typedef std::vector<std::string> nameList;


// Concrete Class Watopoly Controller will receive all commands from the player
//   and interact with the kernel of the game to produce and calculate the
//   outputs of the game.
class Controller {
    int seed = 0;
    int additionalPlayer = 1;
    bool seedPermit = false;
    bool testPermit = false;
    std::string cmd;
    gridPtr grid;
    std::vector<playerPtr> playerList;
    
    // std::shared_ptr<nameList> playerListInitializer will produce a
    //   character name list that current game can hold.
    //   Note that the default mode can only hold the following characters:
    //   - G: Goose
    //   - B: GRT Bus
    //   - D: Tim Hortons Doughnut
    //   - P: Professor
    //   - S: Student
    //   - $: Money
    //   - L: Laptop
    //   - T: Pink tie
    std::shared_ptr<nameList> listInitializer(void) const noexcept;
    
    // int Controller::listPosition(const char &, nameList &) will
    //   check if the given character is one character of the given
    //   namelist. It will return the correct position of in the namelist
    //   if the given character is one character of the given namelist.
    //   It will return false otherwise.
    int listPosition(const char &, const nameList &) const noexcept;
    
    // void nextPlayer(int &) will change the number of the currentPlayer
    void nextPlayer(int &) noexcept;
    
    // playerPtr findPlayer(const std::string &) will return the position
    //   of the player matching the given name in the playerList. If
    //   there is no such player in the game, then return nullptr.
    Player *findPlayer(const std::string &) noexcept;
    
    // const bool isNum(const char &) will return true if the given char
    //   is between '0' and '9'.
    const bool isNum(const char &) const noexcept;
    
    // const bool checkWin(void) will return true if there is only one player
    //   remaining.
    const bool checkWin(void) const noexcept;
public:
    // Constructor of Controller
    explicit Controller();
    
    // void GameInit(void) will initialze all data fields in the object
    //   Note that
    //   1. The object should be empty (has not been used).
    //   2. This function is not work as a constructor, all fields have
    //      been allocated when the client call the constructor.
    void GameInit(void);
    
    // void GamePlay(void) will start to play the game and ready to receive
    //   commands and arguments from the players.
    void GamePlay(void);
    
    // void GameLoad(std::ifstream &) will read all stored data in the
    //   given file and set all value in the object.
    void GameLoad(std::ifstream &);
    
    // void GameSave(std::osfstream &) will store all the data in the
    //   current game in the given file.
    void GameSave(std::ofstream &);
    
    // void GameTest(void) will make the Watopoly Game in the Testing mode
    //   This roll will be called roll <die1> <die2>.
    //   The player will move the sum of die1 and die2, where each is ANY
    //   non-negative value and not necessarily between 1 and 6.
    void GameTest(void) noexcept;
    
    // void GameSeed(int &) will set the seed of the object of
    //   Controller
    void GameSeed(const int &) noexcept;
    
    // void GamePrint(void) will print the current map.
    void GamePrint(void) noexcept;
    
    // void controllerClean(void) will prevent the memory leak
    void controllerClean(void);

    // Destructor of Controller
    ~Controller();
};

#endif
