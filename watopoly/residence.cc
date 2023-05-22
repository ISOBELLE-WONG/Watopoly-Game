#include "residence.h"


// Constructor of Residence
Residence::Residence(const std::string &name, const std::string &type, const int &purchaseCost): Ownable(name, type, true, false, purchaseCost) { }


// const int getTotalCost(void) will return the total cost that
//   the player has paid for the property
const int Residence::getTotalCost(void) { return purchaseCost; }


// const int Residence::getTuition(playerPtr p) will return the amount
//   of money that the player should pay.
const int Residence::getTuition(Player &p) {
    if (!getOwner()) { return 0; }
    if (checkMortgage()) { return 0; }
    int tuition = 25;
    for (int i = 0; i < (int)monopolyList.size(); i += 1) {
        if (monopolyList.at(i)->getOwner() == getOwner()) {
            tuition *= 2;
        }
    }
    return tuition;
}


// void Residence::improve(void) will improve the property.
void Residence::improve(void) {
    std::cout << "Sorry, this building is not improvable." << std::endl;
}


// void degenerate(void) will degenerate the property.
void Residence::degenerate(void) {
    std::cout << "Sorry, this building is not degeneratable." << std::endl;
}


// void Residence::setImprovmentLevel(const int level) will set the
//   improvement level directly
void Residence::setImprovmentLevel(const int level) { return; }


// const bool Residence::checkOtherImprove(void) will return true if
//   the property in the same monopoly set is improved.
//   This function will return false otherwise.
const bool Residence::checkOtherImprove(void) { return false; }


// Destructor of Residence
Residence::~Residence() { }
