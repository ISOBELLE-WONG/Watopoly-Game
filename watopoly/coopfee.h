#ifndef coopfee_hpp
#define coopfee_hpp


#include <memory>
#include "player.h"
#include "unownable.h"


class CoopFee;


typedef std::shared_ptr<CoopFee> coopPtr;


class CoopFee: public Unownable {
public:
    // Constructor of CoopFee
    CoopFee();
    
    // const int getTuition(playerPtr) will return the amount
    //   of money that the player should pay.
    virtual const int getTuition(Player &p);
};

#endif
