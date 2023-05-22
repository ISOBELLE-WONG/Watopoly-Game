#ifndef __UNOWNABLE_H__
#define __UNOWNABLE_H__


#include <memory>
#include "player.h"
#include "property.h"


class Unownable;


typedef std::shared_ptr<Unownable> unownablePtr;


class Unownable: public Property {
public:
    // Constructor of Unownable
    explicit Unownable(const std::string &, const bool &);
    
    // const int getTuition(playerPtr) will return the amount
    //   of money that the player should pay.
    virtual const int getTuition(Player &);
    
    // const std::string getMovement(playerPtr) will return the instruction
    //   that the position or the steps that the player should move.
    virtual const std::string getMovement(Player *) noexcept;
    
    // std::string getGuest(void) will return the guestList of this
    //   property
    virtual std::string getGuest(void) override;
    
    // const int getImproveLevel(void) will return the
    //   improvement level that the current building has.
    virtual const int getImproveLevel(void);
    
};

#endif
