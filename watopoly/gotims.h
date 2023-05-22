#ifndef __GOTIMS_H__
#define __GOTIMS_H__


#include <memory>
#include "player.h"
#include "unownable.h"


class GoTims;


typedef std::shared_ptr<GoTims> goPtr;


class GoTims: public Unownable {
public:
    // Constructor of GoTims
    GoTims();
    
    // const std::string getMovement(playerPtr) will return the instruction
    //   that the position or the steps that the player should move.
    virtual const std::string getMovement(Player *) noexcept;
};

#endif
