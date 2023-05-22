#ifndef __GOOSE_H__
#define __GOOSE_H__


#include <memory>
#include "player.h"
#include "unownable.h"


class Goose;


typedef std::shared_ptr<Goose> gooPtr;


class Goose: public Unownable {
public:
    // Constructor of Goose
    Goose();
    
    // const int getTuition(playerPtr) will return the amount
    //   of money that the player should pay.
    virtual const int getTuition(Player &p);
};

#endif
