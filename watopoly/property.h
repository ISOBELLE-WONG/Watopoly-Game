#ifndef __PROPERTY_H__
#define __PROPERTY_H__


#include <iostream>
#include <memory>
#include <string>
#include <vector>
// #include "player.hpp"


class Player;
class Property;


typedef std::shared_ptr<Property> propertyPtr;
typedef std::shared_ptr<Player> playerPtr;


class Property {
protected:
    const bool movable;
    const bool ownable;
    Property *next;
    Property *prev;
    const std::string name;
    const std::string type;
    std::vector<Player *> guestList;
    std::vector<Property *> monopolyList;
public:
    // Constructor of Property
    Property(const std::string &, const std::string &, const bool &, const bool &);
    
    // const bool getMovable(void) will return true if this
    //   property will contains the event that will make the
    //   player move, false, otherwise.
    const bool getMovable(void) const noexcept;
    
    // const bool getOwnable(void) will return true if this
    //   property is ownable, false otherwise.
    const bool getOwnable(void) const noexcept;
    
    // const std::string getName(void) will return the name of
    //   this property.
    const std::string getName(void) const noexcept;
    
    // const std::string getType(void) will return the type of
    //   this property.
    const std::string getType(void) const noexcept;
    
    // playerPtr getOwner(void) will return the owner of this Property.
    virtual Player *getOwner(void) noexcept;
    
    // std::string getGuest(void) will return the guestList of this
    //   property
    virtual std::string getGuest(void) = 0;
    
    // propertyPtr getNext(void) will return the pointer of next
    //   property connexted to the current property
    Property *getNext(void) noexcept;
    
    // propertyPtr getPrev(void) will return the pointer of next
    //   property connexted to the current property
    Property *getPrev(void) noexcept;
    
    // void setNext(propertyPtr) will set the next of the property
    //   as the given property.
    void setNext(Property *) noexcept;
    
    // void setNext(propertyPtr) will set the previous of the
    //   property as the given property.
    void setPrev(Property *) noexcept;
    
    // void setTime(const int) will set the time of the DC
    //   Tims stuck event
    virtual void setTime(const int);
    
    // void attachGuest(playerPtr p, bool isDC = false) will set the given
    //   player as a guest.
    virtual void attachGuest(Player *p, bool isDC = false) noexcept;
    
    // void attachMonopoly(propertyPtr) will make the given
    //   pointer as part of the monopoly set.
    void attachMonopoly(Property *);
    
    // void removeGuest(playerPtr) will remove the
    //   matched player from the guest list.
    virtual void removeGuest(Player &) noexcept;
    
    // const int getTuition(playerPtr) will return the amount
    //   of money that the player should pay.
    virtual const int getTuition(Player &) = 0;
    
    // const std::string getMovement(playerPtr) will return the instruction
    //   that the position or the steps that the player should move.
    virtual const std::string getMovement(Player *) noexcept = 0;
    
    // const int getImproveLevel(void) will return the
    //   improvement level that the current building has.
    virtual const int getImproveLevel(void) = 0;
    
    // void destroy(void) will destory the whole property to
    //   make sure there is no memory leak.
    void destroy(void);
    
    // const int getTime(playerPtr) will provide the time of
    //   the player should still stay in the DC.
    virtual const int getTime(Player *);
    
    // void subTime(playerPtr) will substract the
    //   remaining time of the player.
    virtual void subTime(Player *);
    
    // Destructor of Property
    virtual ~Property();
};


#endif
