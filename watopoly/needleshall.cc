#include "needleshall.h"


// Constructor of NeedlesHall
NeedlesHall::NeedlesHall(): Unownable("Needles Hall", false) { }


// const int NeedlesHall::getTuition(playerPtr p) will return the amount
//   of money that the player should pay.
const int NeedlesHall::getTuition(Player &p) {
    srand((unsigned)time(0));
    double seed = (rand() % 100) / 100.0;

    if (seed == 0) {
        p.addCup(1);
    }

    srand((unsigned)time(0));
    seed = (rand() % 100) / 100.0;
    
    if (seed <= (1.0 / 18.8)) {
        return 200;
    } else if (seed <= 1.0 / 6.0) {
        return 100;
    } else if (seed <= 1.0 / 3.0) {
        return -50;
    } else if (seed <= 2.0 / 3.0) {
        return 25;
    } else if (seed <= 2.0 / 3.0 + 1.0 / 6.0) {
        return 50;
    } else if (seed <= 2.0 / 3.0 + 1.0 / 6.0 + 1.0 / 9.0) {
        return 100;
    } else {
        return 200;
    }
}


