#ifndef __DCTIMS_H__
#define __DCTIMS_H__


#include <memory>
#include <ctime>
#include "player.h"
#include "unownable.h"


class DCTims;


typedef std::shared_ptr<DCTims> DCTPtr;



class DCTims: public Unownable {
    std::vector<int> timeList;
public:
    // Constructor of SLC
    DCTims();
    
    // const int getTuition(playerPtr) will return the amount
    //   of money that the player should pay.
    virtual const int getTuition(Player &p);
    
    // void attachGuest(playerPtr) will set the given
    //   player as a guest.
    virtual void attachGuest(Player *p, bool isDC = false) noexcept;
    
    // void removeGuest(playerPtr) will remove the
    //   matched player from the guest list.
    virtual void removeGuest(Player &) noexcept;
    
    // const int getTime(playerPtr) will provide the time of
    //   the player should still stay in the DC.
    virtual const int getTime(Player *);
    
    // void subTime(playerPtr) will substract the
    //   remaining time of the player.
    virtual void subTime(Player *);
};

#endif
