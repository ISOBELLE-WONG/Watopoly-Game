#include "unownable.h"


// Constructor of Unownable
Unownable::Unownable(const std::string &name, const bool &movable):
    Property(name, "EVENT", false, movable) { }


// const int Unownable::getTuition(playerPtr p) will return the amount
//   of money that the player should pay.
const int Unownable::getTuition(Player &p) { return 0; }


// const std::string Unownable::getMovement(playerPtr p) will return the instruction
//   that the position or the steps that the player should move.
const std::string Unownable::getMovement(Player *p) noexcept { return "0"; }


// const int Unownable::getImproveLevel(void) will return the
//   improvement level that the current building has.
const int Unownable::getImproveLevel(void) { return 0; }


// std::string Unownable::getGuest(void) will return the guestList of this
//   property
std::string Unownable::getGuest(void) {
    std::string guests = "";
    for (int i = 0; i < (int)guestList.size(); i += 1) {
        guests += (guestList[i]->getSymbol());
    }
    return guests;
}
