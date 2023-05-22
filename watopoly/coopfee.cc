#include "coopfee.h"


// Constructor of CoopFee
CoopFee::CoopFee(): Unownable("Coop Fee", false) { }


// const int getTuition(playerPtr) will return the amount
//   of money that the player should pay.
const int CoopFee::getTuition(Player &p) {
    return 150;
}
