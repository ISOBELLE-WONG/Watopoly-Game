#include "academic.h"


static const int NO_COST = 0;
static const Player *BANK = nullptr;
static const int MINIMUM_LEVEL = 0;
static const int MAXIMUM_LEVEL = 6;


// Constructor of Academic
Academic::Academic(const std::string &name, const std::string &type,
                   const int &purchaseCost, const pl &payList):
    Ownable(name, type, true, true, purchaseCost) {
        this->payList.improveCost = payList.improveCost;
        this->payList.data.clear();
        for (int i = MINIMUM_LEVEL; i < MAXIMUM_LEVEL; i += 1) {
            this->payList.data.emplace_back(payList.data[i]);
        }
}


// virtual const int Academic::getTotalCost(void) will return the total
//   cost that  the player has paid for the property
const int Academic::getTotalCost(void) {
    return getPrice() + getImproveLevel() * payList.improveCost;
}


// const int Academic::getTuition(Player &p) will return the amount
//   of money that the player should pay.
const int Academic::getTuition(Player &p) {
    if (getOwner() == BANK) {
        return NO_COST;
    }
    if (checkMortgage()) { return NO_COST; }
    bool doubleTheTuition = true;
    for (int i = 0; i < (int)monopolyList.size(); i += 1) {
        if (monopolyList.at(i)->getOwner() != getOwner()) {
            doubleTheTuition = false;
        }
    }
    if (!improveLevel) {
        if (doubleTheTuition) {
            owner->takeTuition(payList.data[improveLevel] * 2, this);
        } else {
            owner->takeTuition(payList.data[improveLevel], this);
        }
    } else {
        owner->takeTuition(payList.data[improveLevel], this);
    }
    return payList.data[getImproveLevel()];
}


// void Academic::improve(void) will improve the property.
void Academic::improve(void) {
    for (int i = 0; i < (int)monopolyList.size(); i += 1) {
        if (monopolyList.at(i)->getOwner() != getOwner()) {
            std::cout << "Some of property of this monopoly set is not belong to you!" << std::endl;
            std::cout << "Improvement fails." << std::endl;
            return;
        }
    }
    if (getImproveLevel() < MAXIMUM_LEVEL) {
        getOwner()->pay(payList.improveCost);
        improveLevel += 1;
    } else {
        std::cout << getName() << " has already improved into the maximum level!" << std::endl;
        std::cout << "Improvement fails." << std::endl;
    }
}


// void Academic::degenerate(void) will degenerate the property.
void Academic::degenerate(void) {
    for (int i = 0; i < (int)monopolyList.size(); i += 1) {
        if (monopolyList.at(i)->getOwner() != getOwner()) {
            std::cout << "Some of property of this monopoly set is not belong to you!" << std::endl;
            std::cout << "Improvement fails." << std::endl;
            return;
        }
    }
    if (getImproveLevel() < MAXIMUM_LEVEL) {
        getOwner()->pay(payList.improveCost);
        improveLevel += 1;
    } else {
        std::cout << getName() << " has already improved into the maximum level!" << std::endl;
        std::cout << "Improvement fails." << std::endl;
    }
}


// void Academic::setImprovmentLevel(const int) will set the
//   improvement level directly
void Academic::setImprovmentLevel(const int _improveLevel) {
    improveLevel = _improveLevel;
}


// const int Academic::getImproveLevel(void) will return the
//   improvement level that the current building has.
const int Academic::getImproveLevel(void) { return improveLevel; }


// const bool Academic::checkOtherImprove(void) will return true if
//   the property in the same monopoly set is improved.
//   This function will return false otherwise.
const bool Academic::checkOtherImprove(void) {
    for (int i = 0; i < (int)monopolyList.size(); i += 1) {
        if (monopolyList.at(i)->getOwner() != getOwner()) {
            return false;
        }
    }
    return true;
}


// Destructor of Academic
Academic::~Academic() { }
