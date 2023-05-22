#include "slc.h"


// Constructor of SLC
SLC::SLC(): Unownable("SLC", true) { }


// const std::string SLC::getMovement(playerPtr p) will return the instruction
//   that the position or the steps that the player should move.
const std::string SLC::getMovement(Player *p) noexcept {
    srand((unsigned)time(0));
    double seed = (rand() % 100) / 100.0;
    
    if (seed == 0) {
        p->addCup(1);
    }
    
    srand((unsigned)time(0));
    seed = (rand() % 100) / 100.0;
    
    if (seed <= (1.0 / 8.0)) {
        return "-3";
    } else if (seed <= (1.0 / 8.0 + 1.0 / 6.0)) {
        return "-2";
    } else if (seed <= (1.0 / 8.0 + 1.0 / 3.0)) {
        return "-1";
    } else if (seed <= (1.0 / 4.0 + 1.0 / 3.0)) {
        return "1";
    } else if (seed <= (1.0 / 4.0 + 1.0 / 3.0 + 1.0 / 6.0)) {
        return "2";
    } else if (seed <= (1.0 / 4.0 + 2.0 / 3.0)) {
        return "3";
    } else if (seed <= (11.0 / 12.0 + 1.0 / 24.0)) {
        return "DC Tims Line";
    } else {
        return "Collect OSAP";
    }
}
