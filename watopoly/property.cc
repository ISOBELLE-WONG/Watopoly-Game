#include "property.h"


// Constructor of Property
Property::Property(const std::string &name, const std::string &type,
                   const bool &ownable, const bool &movable):
    movable(movable), ownable(ownable), next(nullptr), prev(nullptr),
    name(name), type(type) {
        guestList.clear();
        monopolyList.clear();
}


// const bool Property::getMovable(void) will return true if this
//   property will contains the event that will make the
//   player move, false, otherwise.
const bool Property::getMovable(void) const noexcept { return movable; }


// const bool Property::getOwnable(void) will return true if this
//   property is ownable, false otherwise.
const bool Property::getOwnable(void) const noexcept { return ownable; }


// const std::string Property::getName(void) will return the name of
//   this property.
const std::string Property::getName(void) const noexcept { return name; }


// const std::string Property::getType(void) will return the type of
//   this property.
const std::string Property::getType(void) const noexcept { return type; }


// playerPtr Property::getOwner(void) will return the owner of this Property.
Player *Property::getOwner(void) noexcept { return nullptr; }


// propertyPtr Property::getNext(void) will return the pointer of next
//   property connexted to the current property
Property *Property::getNext(void) noexcept { return next; }


// propertyPtr Property::getPrev(void) will return the pointer of next
//   property connexted to the current property
Property *Property::getPrev(void) noexcept { return prev; }


// void Property::setNext(propertyPtr _next) will set the next of
//   the property as the given property.
void Property::setNext(Property *_next) noexcept { next = _next; }


// void Property::setNext(propertyPtr _next) will set the previous of
//   the property as the given property.
void Property::setPrev(Property *_prev) noexcept { prev = _prev; }


// void Property::setTime(const int time) will set the time of the DC
//   Tims stuck event
void Property::setTime(const int time) { }


// void Property::attachGuest(playerPtr p, bool isDC) will set the given
//   player as a guest.
void Property::attachGuest(Player *p, bool isDC) noexcept {
    guestList.emplace_back(p);
}


// void attachMonopoly(propertyPtr property) will make the given
//   pointer as part of the monopoly set.
void Property::attachMonopoly(Property *property) {
    monopolyList.emplace_back(property);
}


// void Property::removeGuest(playerPtr guest) will remove the
//   matched player from the guest list.
void Property::removeGuest(Player &guest) noexcept {
    for (int i = 0; i < (int)guestList.size(); i += 1) {
        if (guestList.at(i) == &guest) {
            guestList.erase(guestList.begin() + i);
        }
    }
}


// const int getTime(playerPtr) will provide the time of
//   the player should still stay in the DC.
const int Property::getTime(Player *) { return 0; }


// void subTime(playerPtr) will substract the
//   remaining time of the player.
void Property::subTime(Player *) { return; }


// void Property::destroy(void) will destory the whole property to
//   make sure there is no memory leak.
void Property::destroy(void) {
    for (int i = 0; i < (int)guestList.size(); i += 1) {
        guestList[i] = nullptr;
    }
    guestList.clear();
    for (int i = 0; i < (int)monopolyList.size(); i += 1) {
        monopolyList[i] = nullptr;
    }
    monopolyList.clear();
    setNext(nullptr);
    setPrev(nullptr);
}


// Destructor of Property
Property::~Property() { }
