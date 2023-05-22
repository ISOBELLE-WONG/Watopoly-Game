#ifndef __OSAP_H__
#define __OSAP_H__


#include <memory>
#include "unownable.h"


class OSAP;


typedef std::shared_ptr<OSAP> OSAPPtr;


class OSAP: public Unownable {
public:
    // Constructor of OSAP
    explicit OSAP();
    
    // const int getTuition(void) will return the amount
    //   of money that the player should pay.
    virtual const int getTuition(Player &p) override;
};

#endif
