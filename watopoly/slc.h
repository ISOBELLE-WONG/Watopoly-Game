#ifndef __SLC_H__
#define __SLC_H__


#include <ctime>
#include <random>
#include <memory>
#include "player.h"
#include "unownable.h"


class SLC;


typedef std::shared_ptr<SLC> SLCPtr;


class SLC: public Unownable {
public:
    // Constructor of SLC
    SLC();
    
    // const std::string getMovement(playerPtr) will return the instruction
    //   that the position or the steps that the player should move.
    virtual const std::string getMovement(Player *) noexcept;
};


#endif
