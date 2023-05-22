#ifndef __Ownable_H__
#define __Ownable_H__


#include <iostream>
#include <memory>
#include "player.h"
#include "property.h"


class Player;
class Ownable;


typedef std::shared_ptr<Ownable> ownablePtr;
typedef std::shared_ptr<Player> playerPtr;


class Ownable: public Property {
protected:
    const bool improvable;
    Player *owner = nullptr;
    int purchaseCost = 0;
public:
    // Constructor of Ownable
    explicit Ownable(const std::string &, const std::string &,
                          const bool &, const bool &, const int &);
    
    // virtual const int getTotalCost(void) will return the total cost that
    //   the player has paid for the property
    virtual const int getTotalCost(void) = 0;
    
    // const bool getImproveable(void) will return true, if the building
    //   is improvable, false otherwise.
    virtual const bool getImproveable(void);
    
    // void improve(void) will improve the property.
    virtual void improve(void) = 0;
    
    // void degenerate(void) will degenerate the property.
    virtual void degenerate(void) = 0;
    
    // void setImprovmentLevel(const int) will set the
    //   improvement level directly
    virtual void setImprovmentLevel(const int) = 0;
    
    // const int getImproveLevel(void) will return the
    //   improvement level that the current building has.
    virtual const int getImproveLevel(void);
    
    // const bool checkOtherImprove(void) will return true if
    //   the property in the same monopoly set is improved.
    //   This function will return false otherwise.
    virtual const bool checkOtherImprove(void) = 0;
    
    // void setOwner(playerPtr) will set the owner of this
    //   property
    virtual void setOwner(Player *);
    
    // playerPtr getOwner(void) will return the owner of this Property.
    virtual Player *getOwner(void) noexcept;
    
    // std::string getGuest(void) will return the guestList of this
    //   property
    virtual std::string getGuest(void) override;
    
    // const int getPrice(void) will return the purchase cost
    //   of this property.
    virtual const int getPrice(void);
    
    // const std::string getMovement(playerPtr) will return the instruction
    //   that the position or the steps that the player should move.
    virtual const std::string getMovement(Player *) noexcept;
    
    // const bool checkMortgage(void) will return true if the property
    //   is mortgaged.
    virtual const bool checkMortgage(void);
    
    // Destructor of Ownable
    virtual ~Ownable();
};


#endif
