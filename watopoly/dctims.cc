#include "dctims.h"


// Constructor of DCTims
DCTims::DCTims(): Unownable("DC Tims Line", false) {
    timeList.clear();
}


// const int DCTims::getTuition(playerPtr) will return the amount
//   of money that the player should pay.
const int DCTims::getTuition(Player &p) {
    int pos = 0;
    for (int i = 0; i < (int)timeList.size(); i += 1) {
        if (&p == guestList.at(i)) {
            pos = i;
            break;
        }
    }
    if (timeList.at(pos) == 0) {
        std::cout << "Sorry, you have to pay $50 and leave." << std::endl;
        return 50;
    } else if (timeList.at(pos) == -1) {
        return 0;
    }
    if (p.getCup() == 0) {
        std::cout << "You don't have any roll up the rim cup." << std::endl;
    } else {
        std::cout << "You have " << p.getCup() << " roll up the rim cup" << std::endl;
        std::cout << "Do you want to use one of it?" << std::endl;
        std::cout << "Type Y if you want, N otherwise." << std::endl;
        char choose = 'N';
        while (std::cin >> choose) {
            if (choose == 'Y') {
                p.addCup(-1);
                return 0;
            } else if (choose == 'N') {
                break;
            } else {
                std::cout << "Invalid choose, please type again." << std::endl;
            }
        }
    }
    std::cout << "Do you want to pay $50 to leave?"  << std::endl;
    std::cout << "Type Y if you want, N otherwise." << std::endl;
    char choose = 'N';
    while (std::cin >> choose) {
        if (choose == 'Y') {
            return 50;
        } else if (choose == 'N') {
            break;
        } else {
            std::cout << "Invalid choose, please type again." << std::endl;
        }
    }
    srand((unsigned)time(0));
    int roll1 = (rand() % 6) + 1;
    std::cout << "The first roll is " << roll1 << std::endl;
    srand((unsigned)time(0));
    int roll2 = (rand() % 6) + 1;
    std::cout << "The second roll is " << roll2 << std::endl;
    if (roll1 + roll2 % 2 == 0) {
        std::cout << "You have rolled double!" << std::endl;
        for (int i = 0; i < (int)timeList.size(); i += 1) {
            if (&p == guestList.at(i)) {
                timeList.at(i) = 0;
                break;
            }
        }
    } else {
        std::cout << "Sorry, you have rolled single!" << std::endl;
    }
    return 0;
}


// void DCTims::attachGuest(playerPtr p, bool isDC) will set the given
//   player as a guest.
void DCTims::attachGuest(Player *p, bool isDC) noexcept {
    if (isDC) {
        guestList.emplace_back(p);
        timeList.emplace_back(2);
    } else {
        guestList.emplace_back(p);
        timeList.emplace_back(-1);
    }
}


// void DCTims::removeGuest(playerPtr) will remove the
//   matched player from the guest list.
void DCTims::removeGuest(Player &p) noexcept {
    for (int i = 0; i < (int)timeList.size(); i += 1) {
        if (guestList.at(i) == &p) {
            guestList[i] = nullptr;
            guestList.erase(guestList.begin() + i);
            timeList.erase(timeList.begin() + i);
            break;
        }
    }
}


// const int DCTims::getTime(playerPtr p) will provide the time of
//   the player should still stay in the DC.
const int DCTims::getTime(Player *p) {
    for (int i = 0; i < (int)timeList.size(); i += 1) {
        if (guestList.at(i) == p) {
            return timeList.at(i);
        }
    }
    return -1;
}


// void DCTims::subTime(playerPtr p) will substract the
//   remaining time of the player.
void DCTims::subTime(Player *p) {
    for (int i = 0; i < (int)timeList.size(); i += 1) {
        if (guestList.at(i) == p) {
            timeList.at(i) = timeList.at(i) - 1;
            return;
        }
    }
}

