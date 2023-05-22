#include "ownable.h"


// Constructor of Ownable
Ownable::Ownable(const std::string &name, const std::string &type,
                 const bool &ownable, const bool &improvable, const int &purchaseCost):
    Property(name, type, ownable, false), improvable(improvable), owner(nullptr),
    purchaseCost(purchaseCost) { }


// const bool Ownable::getImproveable(void) will return true, if the building
//   is improvable, false otherwise.
const bool Ownable::getImproveable(void) { return improvable; }


// void Ownable::setOwner(playerPtr _owner) will set the owner of this
//   property
void Ownable::setOwner(Player *_owner) { owner = _owner; }


// playerPtr getOwner(void) will return the owner of this Property.
Player *Ownable::getOwner(void) noexcept { return owner; }


// std::string Ownable::getGuest(void) will return the guestList of this
//   property
std::string Ownable::getGuest(void) {
    std::string guests = "";
    for (int i = 0; i < (int)guestList.size(); i += 1) {
        guests += (guestList[i]->getSymbol());
    }
    return guests;
}


// const int Ownable::getImproveLevel(void) will return the
//   improvement level that the current building has.
const int Ownable::getImproveLevel(void) { return 0; }


// const int Ownable::getPrice(void) will return the purchase cost
//   of this property.
const int Ownable::getPrice(void) { return purchaseCost; }


// const std::string Ownable::getMovement(playerPtr) will return the instruction
//   that the position or the steps that the player should move.
const std::string Ownable::getMovement(Player *p) noexcept { return "0"; }


// const bool Ownable::checkMortgage(void) will return true if the property
//   is mortgaged.
const bool Ownable::checkMortgage(void) {
    return owner->checkMortgage(this);
}


// Destructor of Ownable
Ownable::~Ownable() { }
