#include "osap.h"


// Constructor of OSAP
OSAP::OSAP(): Unownable("Collect OSAP", false) { }


// const int OSAP::getTuition(playerPtr p) will return the amount
//   of money that the player should pay.
const int OSAP::getTuition(Player &p) { return -200; }
