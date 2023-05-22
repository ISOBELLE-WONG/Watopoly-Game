#include "goose.h"


// Constructor of Goose
Goose::Goose(): Unownable("Goose Nesting", false) { }


// const int Goose::getTuition(playerPtr) will return the amount
//   of money that the player should pay.
const int Goose::getTuition(Player &p) {
    std::cout << "A flock of nesting geese are attacking you." << std::endl;
    return 0;
}
