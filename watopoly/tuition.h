#ifndef __TUITION_H__
#define __TUITION_H__


#include <memory>
#include "player.h"
#include "unownable.h"


class Tuition;


typedef std::shared_ptr<Tuition> tuitPtr;


class Tuition: public Unownable {
public:
    // Constructor of Tuition
    Tuition();
    
    // const int getTuition(playerPtr) will return the amount
    //   of money that the player should pay.
    virtual const int getTuition(Player &p);
};

#endif
