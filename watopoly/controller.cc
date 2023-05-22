#include "controller.h"


// ============================================================================
// Static fields

static const int START_POSITION = 0;
// should be changed to 6 later
static const int MINIMUM_PLAYER = 2;
static const int INVALID_POSITION = -1;

// ============================================================================
// Public methods of Controller

// Constructor of Controller
Controller::Controller():
    seed{(int)std::chrono::system_clock::now().time_since_epoch().count()},
    cmd{""}, grid{std::make_shared<Grid>(seed)} {
        std::cout << "Watopoly Game is initialized ..." << std::endl;
        playerList.clear();
}


// void Controller::GameInit(void) will initialze all data
//   fields in the object.
//   Note that:
//      This function is not work as a constructor, all fields have
//      been allocated when the client call the constructor. This
//      function will perpare all necessary data for the game.
void Controller::GameInit(void) {
    int playNum = 0, startingPos = START_POSITION;
    std::cout << "Please input the number of the player in this game: " << std::endl;
    while (std::cin >> playNum) {
        if (std::cin.good()) {
            if (MINIMUM_PLAYER <= playNum &&
                playNum <= 7) {
                break;
            } else {
                std::cout << "That is not a valid input, please input again:" << std::endl;
            }
        } else {
            std::cout << "That is not a valid input, please input again:" << std::endl;
            std::cin.ignore();
            std::cin.clear();
        }
        std::cout << "Please input the number of the player in this game: " << std::endl;
    }
    if (std::cin.eof()) { return; }
    std::cout << "Please input one character for the symbol of the character." << std::endl;
    std::cout << "Note that we have the following original player." << std::endl;
    std::shared_ptr<nameList> characterList = listInitializer();
    std::cout << "List of Player:" << std::endl;
    for (int i = 0; i < (int)characterList->size(); i += 1) {
        std::cout << "- " << characterList->at(i) << std::endl;
    }
    std::cout << "Note that you can still choose:" << std::endl;
    std::cout << (int)characterList->size() << " original player" << std::endl;
    std::cout << additionalPlayer << " additional player" << std::endl;
    std::cout << "Please input the symbol of the player you want to play: " << std::endl;
    while (std::cin >> cmd) {
        if (cmd == "OK") {
            std::cout << "That is all the player you want? OK~" << std::endl;
            break;
        }
        if ((int)cmd.size() > 1) {
            std::cout << "That is not a valid symbol of the player!" << std::endl;
            std::cout << "Please input again:" << std::endl;
            continue;
        }
        if ((int)playerList.size() == playNum) {
            std::cout << "The number of player is enough now!" << std::endl;
            break;
        }
        if (!(additionalPlayer + (int)characterList->size())) {
            std::cout << "You have the maximum number of player that this game can hold!" << std::endl;
            break;
        }
        int findPos = listPosition(cmd[0], *characterList);
        if (findPos != INVALID_POSITION) {
            std::cout << "The player you choose is one of the original player that the game provides~" << std::endl;
            std::cout << "The player information: " << characterList->at(findPos) << std::endl;
            playerList.emplace_back(playerPtr(new Player{
                grid->at(startingPos).get(), cmd[0],
                characterList->at(findPos).replace(0, 3, "")}));
            characterList->erase(characterList->begin() + findPos);
            std::cout << "The player has been loaded in the list of player" << std::endl;
        } else if (additionalPlayer) {
            std::cout << "The player symbol you input is not one of the original player." << std::endl;
            std::cout << "How do you want to name this player?" << std::endl;
            std::string playerName = "";
            std::cin >> playerName;
            if (std::cin.fail()) { break; }
            playerList.emplace_back(playerPtr(new Player{
                grid->at(startingPos).get(), cmd[0], playerName}));
            additionalPlayer -= 1;
        } else {
            std::cout << "You cannot choose more additional player!" << std::endl;
        }
        if ((int)playerList.size() == playNum) {
            std::cout << "The number of player is enough now!" << std::endl;
            break;
        }
        if (!(additionalPlayer + (int)characterList->size())) {
            std::cout << "You have the maximum number of player that this game can hold!" << std::endl;
            break;
        }
        std::cout << "Note that you can still choose:" << std::endl;
        std::cout << characterList->size() << " original player" << std::endl;
        std::cout << additionalPlayer << " additional player" << std::endl;
        std::cout << "Please input the symbol of the player you want to play: " << std::endl;
    }
    if (std::cin.eof()) { return; }
    if (MINIMUM_PLAYER > playNum) {
        throw "We don't have enough player to start the game.";
    }
    for (int i = 0; i < (int)playerList.size(); i += 1) {
        std::cout << "Player: " << playerList[i]->getName() << "(" << playerList[i]->getSymbol() << ")";
        std::cout << " has been located at " << grid->at(startingPos)->getName()<< std::endl;
        grid->at(startingPos)->attachGuest(playerList[i].get());
    }
    grid->gridAttach();
    grid->gridPrint();
}


// void Controller::GamePlay(void) will start to play the game
//   and ready to receive commands and arguments from the players.
void Controller::GamePlay(void) {
    if ((int)playerList.size() < 2) {
        std::cout << "We don't have enough player to start the game." << std::endl;
	return;
    }
    std::cout << "Watopoly Game starts!" << std::endl;
    bool bankR = false;
    int currPlayerNum = 0;
    int money, roll1, roll2;
    std::string trader, filename, give, receive, property, decision;
    std::vector<int> playRoll = {1, 2, 3, 4, 5, 6};
    while (true) {
	bankR = false;
        if (!seedPermit) {
            seed = (int)std::chrono::system_clock::now().time_since_epoch().count();
        }
        playerPtr currPlayer = playerList[currPlayerNum];
        std::cout << currPlayer->getName() << " wants to: " << std::endl;
        std::cin >> cmd;
        if (std::cin.fail()) { break; }
        if (cmd == "roll") {
            if (currPlayer->moneyOwned) { continue; }
            if (!currPlayer->getMovable()) {
                std::cout << currPlayer->getName() << " cannot move!";
                std::cout << std::endl;
                continue;
            }
            if (testPermit) {
                std::cin >> roll1 >> roll2;
            } else {
                std::default_random_engine rng{(unsigned)seed};
                std::shuffle(playRoll.begin(), playRoll.end(), rng);
                roll1 = *playRoll.begin();
                std::shuffle(playRoll.begin(), playRoll.end(), rng);
                roll2 = *playRoll.begin();
            }
            currPlayer->move(roll1 + roll2);
            currPlayer->makeAction();
            while (currPlayer->getLanding()->getMovable()) {
                currPlayer->makeAction();
            }
        } else if (cmd == "next") {
            if (currPlayer->moneyOwned) { continue; }
            if (!currPlayer->movalready) { continue; }
            currPlayer->moveReset();
            nextPlayer(currPlayerNum);
        } else if (cmd == "trade") {
            std::cin >> trader >> give >> receive;
            if (std::cin.fail()) { break; }
            Player *traderPtr = findPlayer(trader);
            if (!traderPtr) { continue; }
            if (trader == currPlayer->getName()) {
                std::cout << "You cannot trade with yourself." << std::endl;
                continue;
            }
            if (isNum(give[0] && isNum(receive[0]))) { continue; }
            try {
                if (isNum(give[0])) {
                    money = std::stoi(give);
                } else if (isNum(receive[0])) {
                    money = std::stoi(receive);
                }
            } catch (std::invalid_argument &e) {
                continue;
            }
            if (isNum(give[0])) {
                currPlayer->tradeWith(traderPtr, money, receive);
            } else if (isNum(receive[0])) {
                currPlayer->tradeWith(traderPtr, give, money);
            } else {
                currPlayer->tradeWith(traderPtr, give, receive);
            }
        } else if (cmd == "improve") {
            std::cin >> property >> decision;
            if (std::cin.fail()) { break; }
            if (decision == "buy") {
                currPlayer->improve(property);
            } else if (decision == "sell") {
                currPlayer->degenerate(property);
            }
        } else if (cmd == "mortgage") {
            std::cin >> property;
            if (std::cin.fail()) { break; }
            currPlayer->mortgage(property);
        } else if (cmd == "unmortgage") {
            std::cin >> property;
            if (std::cin.fail()) { break; }
            currPlayer->unmortgage(property);
        } else if (cmd == "bankrupt") {
            if (currPlayer->moneyOwned) {
                if (currPlayer->lastPropertyOwner == nullptr) {
                    currPlayer->turnPublic();
                } else {
                    currPlayer->turnPrivate(currPlayer->lastPropertyOwner);
                }
                playerList.erase(playerList.begin() + currPlayerNum);
                if (currPlayerNum == (int)playerList.size()) {
                    currPlayerNum = 0;
                }
		bankR = true;
            } else {
                std::cout << "You cannot not be bankruptted." << std::endl;
            }
        } else if (cmd == "assets") {
            currPlayer->showAssets();
        } else if (cmd == "all") {
            std::cout << "Now, we have the current situation:" << std::endl;
            for (int i = 0; i < (int)playerList.size(); i += 1) {
                playerList[i]->showAssets();
            }
        } else if (cmd == "save") {
            try {
                std::cin >> filename;
                if (std::cin.fail()) { throw ""; }
            } catch (const std::string &) {
                std::cin.clear();
                std::cin.ignore();
                filename = "gameData.txt";
            }
            std::ofstream saveFile{filename};
            if (saveFile.fail()) { continue; }
            GameSave(saveFile);
        } else if (cmd == "quit") {
	    return;
	} else {
            continue;
        }
        if (currPlayer->moneyOwned && !bankR) {
            std::cout << "You have to pay the money!" << std::endl;
            std::cout << "Or you can choose to bankrupt" << std::endl;
            currPlayer->payDebt();
            continue;
        }
        GamePrint();
        if (checkWin()) {
            std::cout << "We have a WINNER: " << playerList[0]->getName() << std::endl;
            std::cout << "Congratulations!" << std::endl;
            break;
        }
        if (!seedPermit) {
            seed = (int)std::chrono::system_clock::now().time_since_epoch().count();
        }
    }
}


// void Controller::GameLoad(std::ifstream &) will read
//   all stored data in the given file and set all value in the object.
void Controller::GameLoad(std::ifstream &loadFile) {
    int playerNum, cupNum, money, position, improvement, stuck, time;
    std::string cmd, playerName, mode, owner, property;
    char playerChar;
    grid->gridAttach();
    loadFile >> playerNum;
    if (loadFile.fail()) { return; }
    for (int i = 0; i < playerNum; i += 1) {
        loadFile >> playerName >> playerChar >> cupNum >> money >> position;
	std::cout << "Player Information: " << std::endl;
	std::cout << "- " << playerName << " " << playerChar << " ";
	std::cout << cupNum << " " << money << " " << position << std::endl;
        if (loadFile.fail()) { return; }
        std::shared_ptr<nameList> characterList = listInitializer();
        for (int i = 0; i < (int)characterList->size(); i += 1) {
            if (playerChar == characterList->at(i)[0]) {
                playerName = characterList->at(i).replace(0, 3, "");
            }
        }
	stuck = false;
	if (position == 10) { loadFile >> stuck; }
        if (stuck) {
            loadFile >> time;
            if (loadFile.fail()) { return; }
        }
        playerPtr currPlayer(new Player{grid->at(position).get(), playerChar, playerName});
        playerList.emplace_back(currPlayer);
	currPlayer->pay(1500 - money);
	grid->at(position)->attachGuest(currPlayer.get(), stuck);
	if (position == 10) {
	    grid->at(position)->setTime(time);
	}
    }
    while (getline(loadFile, mode)) {
        std::stringstream ss{mode};
        ss >> property >> owner >> improvement;
        if (ss.fail()) { return; }
        for (int i = 0; i < (int)playerList.size(); i += 1) {
            if (owner == playerList[i]->getName()) {
                Property *p = grid->find(property).get();
                Ownable *propertyPtr = dynamic_cast<Ownable *>(p);
                playerList[i]->get(propertyPtr);
                break;
            }
        }
    }
    std::cout << "The file is loaded to the game!" << std::endl;
}


// void Controller::GameSave(std::osfstream &) will store
//   all the data in the current game in the given file.
void Controller::GameSave(std::ofstream &saveFile) {
    saveFile << (int)playerList.size() << std::endl;
    for (int i = 0; i < (int)playerList.size(); i += 1) {
        saveFile << playerList[i]->getName() << " ";
        saveFile << playerList[i]->getSymbol() << " ";
        saveFile << playerList[i]->getCup() << " ";
	saveFile << playerList[i]->getCash() << " ";
	saveFile << grid->findPos(playerList[i]->getLanding()->getName()) << " ";
        if (grid->findPos(playerList[i]->getLanding()->getName()) == 10) {
	    if (playerList[i]->getLanding()->getTime(playerList[i].get()) == -1) {
	        saveFile << 0;
	    } else {
	        saveFile << 1 << " " << playerList[i]->getLanding()->getTime(playerList[i].get());
	    }
	}
        saveFile << std::endl;
    }
    grid->gridSave(saveFile);
    std::cout << "All game data is stored!" << std::endl;
}


// void Controller::GameTest(void) will make the Watopoly Game in the Testing mode
//   This roll will be called roll <die1> <die2>.
//   The player will move the sum of die1 and die2, where each is ANY
//   non-negative value and not necessarily between 1 and 6.
void Controller::GameTest(void) noexcept { testPermit = true; }


// void Controller::GameSeed(int &_seed) will set the seed of the object of Controller
void Controller::GameSeed(const int &_seed) noexcept {
    seed = _seed;
    seedPermit = true;
    grid->setSeed(seed);
}


// void GamePrint(void) will print the current map.
void Controller::GamePrint(void) noexcept { grid->gridPrint(); }



// ============================================================================
// Private methods of Controller

// std::shared_ptr<nameList> Controller::playerListInitializer will
//   produce a character name list that current game can hold.
//   Note that the default mode can only hold the following characters:
//   - G: Goose
//   - B: GRT Bus
//   - D: Tim Hortons Doughnut
//   - P: Professor
//   - S: Student
//   - $: Money
//   - L: Laptop
//   - T: Pink tie
std::shared_ptr<nameList> Controller::listInitializer(void)
        const noexcept {
    std::shared_ptr<nameList> characterList = std::shared_ptr<nameList>(new nameList());
    characterList->emplace_back("G: Goose");
    characterList->emplace_back("B: GRT_Bus");
    characterList->emplace_back("D: Tim_Hortons_Doughnut");
    characterList->emplace_back("P: Professor");
    characterList->emplace_back("S: Student");
    characterList->emplace_back("$: Money");
    characterList->emplace_back("L: Laptop");
    characterList->emplace_back("T: Pink_tie");
    return characterList;
}


// int Controller::listPosition(const char &, nameList &) will
//   check if the given character is one character of the given
//   namelist. It will return the correct position of in the namelist
//   if the given character is one character of the given namelist.
//   It will return false otherwise.
int Controller::listPosition(const char &c, const nameList &nl)
        const noexcept {
    for (int i = 0; i < (int)nl.size(); i += 1) {
        if (c == nl[i][0]) {
            return i;
        }
    }
    return INVALID_POSITION;
}


// void Controller::nextPlayer(int &currentPlayerNum) will
//   change the number of the currentPlayer
void Controller::nextPlayer(int &currentPlayerNum) noexcept {
    currentPlayerNum = (currentPlayerNum + 1) % (int)playerList.size();
}


// playerPtr Controller::findPlayer(const std::string &name) will
//   return the pointer of the player matching the given name in the
//   playerList. If there is no such player in the game, then return
//   nullptr.
Player *Controller::findPlayer(const std::string &name) noexcept {
    for (int i = 0; i < (int)playerList.size(); i += 1) {
        if (playerList[i]->getName() == name) {
            return playerList[i].get();
        }
    }
    return nullptr;
}


// const bool Controller::isNum(const char &c) will return true if the
//   given char is between '0' and '9'.
const bool Controller::isNum(const char &c) const noexcept {
    return '0' <= c && c <= '9';
}


// const bool Controller::checkWin(void) will return true if there
//   is only one player remaining.
const bool Controller::checkWin(void) const noexcept {
    return playerList.size() == 1;
}


// void controllerClean(void) will prevent the memory leak
void Controller::controllerClean(void) {
    std::cout << "Cleaning the data ..." << std::endl;
    grid->gridClean();
    for (int i = 0; i < (int)playerList.size(); i += 1) {
        playerList.at(i)->destroy();
    }
}



// Destructor of Controller
Controller::~Controller() { controllerClean(); }

