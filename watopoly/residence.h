#ifndef __RESIDENCE_H__
#define __RESIDENCE_H__


#include <memory>
#include <string>
#include "player.h"
#include "ownable.h"


class Residence;


typedef std::shared_ptr<Residence> resiPtr;


class Residence: public Ownable {
public:
    // Constructor of Residence
    explicit Residence(const std::string &, const std::string &, const int &);
    
    // const int getTotalCost(void) will return the total cost that
    //   the player has paid for the property
    virtual const int getTotalCost(void) override;
    
    // const int getTuition(playerPtr) will return the amount
    //   of money that the player should pay.
    virtual const int getTuition(Player &) override;
    
    // void improve(void) will improve the property.
    virtual void improve(void) override;
    
    // void degenerate(void) will degenerate the property.
    virtual void degenerate(void) override;
    
    // void setImprovmentLevel(const int) will set the
    //   improvement level directly
    virtual void setImprovmentLevel(const int) override;
    
    // const bool checkOtherImprove(void) will return true if
    //   the property in the same monopoly set is improved.
    //   This function will return false otherwise.
    virtual const bool checkOtherImprove(void) override;
    
    // Destructor of Residence
    virtual ~Residence();
};

#endif
