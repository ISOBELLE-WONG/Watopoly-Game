#ifndef __NEEDLESHALL_H__
#define __NEEDLESHALL_H__


#include <memory>
#include <random>
#include "player.h"
#include "unownable.h"


class NeedlesHall;


typedef std::shared_ptr<NeedlesHall> needPtr;


class NeedlesHall: public Unownable {
public:
    // Constructor of NeedlesHall
    NeedlesHall();
    
    // const int getTuition(playerPtr) will return the amount
    //   of money that the player should pay.
    virtual const int getTuition(Player &p);
};

#endif
