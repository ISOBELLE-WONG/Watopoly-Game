#include "tuition.h"


// Constructor of OSAP
Tuition::Tuition(): Unownable("Tuition", false) { }


// const int Tuition::getTuition(playerPtr p) will return the amount
//   of money that the player should pay.
const int Tuition::getTuition(Player &p) {
    std::cout << "You should pay one of the following options:" << std::endl;
    std::cout << "1. Paying $300 tuition." << std::endl;
    std::cout << "2. 10% of your total worth." << std::endl;
    std::cout << "Type 1 if you want to pay $300, 2 if you want to pay 10% of your total worth." << std::endl;
    int choose = 1;
    while (std::cin >> choose) {
        if (std::cin.fail()) {
            std::cin.ignore();
            std::cin.clear();
            std::cout << "That is not a valid choose, please choose again:" << std::endl;
            continue;
        } else if (choose != 1 && choose != 2) {
            std::cout << "That is not a valid choose, please choose again:" << std::endl;
            continue;
        } else {
            break;
        }
    }
    if (choose == 1) {
        return 300;
    } else if (choose == 2) {
        return p.getTotalWorth();
    } else {
        std::cout << "The choose is invalid!" << std::endl;
        return 0;
    }
}
