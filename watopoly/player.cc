#include "player.h"


static const Player *BANK = nullptr;


// Constructor of Player
Player::Player(Property *landing, const char &symbol, const std::string &name):
    symbol(symbol), name(name), landing(landing) {
        ownedList.clear();
        mortgagedList.clear();
}


// const int &Player::getCup(void) will return the number of the cups that
//   the current player holds.
const int &Player::getCup(void) { return cup; }


// void addCup(const int) will add the number of cups to the original
//   number of cup.
void Player::addCup(const int num) {
    if (num > 0) {
        std::cout << "You win " << num << " cup!" << std::endl;
    } else {
        std::cout << "You lose " << -1 * num << " cup!" << std::endl;
    }
    cup += num;
    std::cout << "Now you have " << cup << " cup" << (cup == 1 ? "" : "s") << std::endl;
}


// const int &Player::getCash(void) will return the current cash that
//   the player has.
const int &Player::getCash(void) const { return cashFlow; }


// const bool &Player::getMovable(void) will return true if the object of the
//   Player is movable, false otherwise.
const bool &Player::getMovable(void) { return movable; }


// const std::string &Player::getSymbol(void) will return the symbol of the
//   current object of player.
const char &Player::getSymbol(void) { return symbol; }


// const std::string &Player::getName(void) will return the name of the
//   current object of Player
const std::string &Player::getName(void) { return name; }


// propertyPtr getLanding(void) will return the landing address.
Property *Player::getLanding(void) { return landing; }


// void Player::move(const int &step) will control the object of the Player
//   move the number of given steps.
// Note that the object of the Player will be unmovable!
void Player::move(const int &step) {
    landing->removeGuest(*this);
    std::cout << getName() << " is leaving from " << landing->getName() << std::endl;
    if (step >= 0) {
        for (int i = 0; i < step; i += 1) {
            landing = landing->getNext();
            if (landing->getName() == "Collect OSAP") {
                pay(landing->getTuition(*this));
            }
        }
    } else {
        for (int i = 0; i > step; i -= 1) {
            landing = landing->getPrev();
            if (landing->getName() == "Collect OSAP") {
                pay(landing->getTuition(*this));
            }
        }
    }
    landing->attachGuest(this);
    std::cout << getName() << " is landing at " << landing->getName() << std::endl;
    movable = false;
    movalready = true;
}


// void Player::move(const std::string &target) will control the object
//   of the Player move to the given position.
// Note that the object of the Player will be unmovable!
void Player::move(const std::string &target) {
    std::cout << getName() << " is leaving from " << landing->getName() << std::endl;
    bool OSAPBanned = landing->getName() == "Do To Tims";
    landing->removeGuest(*this);
    while (landing->getName() != target) {
        landing = landing->getNext();
        if (landing->getName() == "Collect OSAP" && !OSAPBanned) {
            pay(landing->getTuition(*this));
        }
    }
    landing->attachGuest(this);
    std::cout << getName() << " is landing at " << landing->getName() << std::endl;
    movable = false;
    movalready = true;
}


// void Player::moveReset(void) will reset the object of the Player to be
//   movable.
void Player::moveReset(void) {
    if (landing->getName() == "DC Tims Line") {
        if (landing->getTime(this) == -1 ||
            landing->getTime(this) == 0) {
        } else {
            landing->subTime(this);
            movable = false;
            movalready = true;
            return;
        }
    }
    movable = true;
    movalready = false;
}


// void Player::makeAction(void) will make action to the landing property.
void Player::makeAction(void) {
    if (landing->getType() == "EVENT") {
        if (landing->getMovable()) {
            bool isStep = true;
            int step = 0;
            std::string target = landing->getMovement(this);
            try {
                step = std::stoi(target);
            }  catch(std::out_of_range &e) {
                isStep = false;
            } catch(std::invalid_argument &e) {
                isStep = false;
            }
            if (isStep) {
                move(step);
            } else {
                move(target);
            }
        } else {
            pay(landing->getTuition(*this));
        }
    } else if (landing->getName() == "Collect OSAP") {
        return;
    } else {
        pay(landing->getTuition(*this));
        if (!landing->getOwner()) {
            std::cout << "This place does not have an owner." << std::endl;
            std::cout << "Do you want to buy this building?" << std::endl;
            std::cout << "Type Y if you want, type N is you don't." << std::endl;
            char choose = 'N';
            while (true) {
                std::cin >> choose;
                if (std::cin.good()) {
                    if (choose == 'Y') {
                        Property *p = landing;
                        // ownablePtr op{dynamic_cast<Ownable *>(p)};
                        buy(dynamic_cast<Ownable *>(p));
                        break;
                    } else if (choose == 'N') {
                        std::cout << "Ok, maybe next time~" << std::endl;
                        break;
                    } else {
                        std::cout << "You should type \'Y\' or \'N\'" << std::endl;
                    }
                } else {
                    std::cin.ignore();
                    std::cin.clear();
                }
            }
        }
    }
}


// void Player::pay(const int tuition) will make the plater pay the give tuition.
void Player::pay(const int tuition) {
    if (getLanding()->getOwnable()) {
        lastPropertyOwner = getLanding()->getOwner();
    } else {
        lastPropertyOwner = nullptr;
    }
//    if (moneyOwned) {
//        if (cashFlow > moneyOwned) {
//            std::cout << "The debt is paid!" << std::endl;
//        }
//    }
    if (cashFlow - tuition < 0 && tuition > 0) {
        moneyOwned = tuition - cashFlow;
        if (lastPropertyOwner) {
            std::cout << "Now you are owned " << lastPropertyOwner->getName() << " $" << moneyOwned << "." << std::endl;
        } else {
            std::cout << "Now you are owned Bank $" << moneyOwned << "." << std::endl;
        }
        return;
    }
    cashFlow -= tuition;
    if (tuition > 0) {
        std::cout << "$" << tuition << " has been removed from " << getName() << "'s  cash flow!" << std::endl;
    } else {
        std::cout << "$" << -1 * tuition << " has been added to " << getName() << "'s cash flow!" << std::endl;
    }
}


// void Player::payDebt(void) will try to pay the owned money.
void Player::payDebt(void) {
    if (getCash() >= moneyOwned) {
        cashFlow -= moneyOwned;
        lastPropertyOwner->pay(-1 * moneyOwned);
        moneyOwned = 0;
        std::cout << "The debt is paid!" << std::endl;
    } else {
        std::cout << "The debt still cannot be paid!" << std::endl;
    }
}



// void Player::buy(ownablePtr property) will make the player buy the
//   give building.
void Player::buy(Ownable *property) {
    if (property->getOwner()) {
        std::cout << "Sorry, this building is owned by" << property->getOwner()->getName() << std::endl;
        std::cout << "If you want this building, you should trade with him." << std::endl;
        return;
    }
    if (getCash() < property->getPrice()) {
        std::cout << "Sorry, you don't have enough money for this building." << std::endl;
        return;
    }
    pay(property->getPrice());
    property->setOwner(this);
    ownedList.emplace_back(property);
}


// void get(ownablePtr property) will make the player get the building
//   without any cost.
void Player::get(Ownable *property) {
    ownedList.emplace_back(property);
    property->setOwner(this);
}


// void Player::improve(const std::string &property) will try to improve the
//   given property
void Player::improve(const std::string &property) {
    for (int i = 0; i < (int)ownedList.size(); i += 1) {
        if (ownedList.at(i)->getName() == property) {
            ownedList.at(i)->improve();
            return;
        }
    }
    std::cout << getName() << " doesn't have the property: " << property;
    std::cout << ", or it is mortgaged already." << std::endl;
}


// void Player::degenerate(const std::string &property) will try to degenerate
//   the give property
void Player::degenerate(const std::string &property) {
    for (int i = 0; i < (int)ownedList.size(); i += 1) {
        if (ownedList.at(i)->getName() == property) {
            ownedList.at(i)->degenerate();
            return;
        }
    }
    std::cout << getName() << " doesn't have the property: " << property;
    std::cout << ", or it is mortgaged already." << std::endl;
}

// void Player::mortgage(const std::string &property) will try to mortgage
//   the given property
void Player::mortgage(const std::string &property) {
    for (int i = 0; i < (int)ownedList.size(); i += 1) {
        if (ownedList.at(i)->getName() == property) {
	    if (ownedList.at(i)->getImproveLevel()) { break; }
            mortgagedList.emplace_back(ownedList.at(i));
            pay(-1 * ownedList.at(i)->getPrice() / 2);
	    ownedList.at(i)->setImprovmentLevel(-1);
            std::cout << ownedList.at(i)->getName() << " is mortgaged to the bank." << std::endl;
            ownedList.erase(ownedList.begin() + i);
            return;
        }
    }
    std::cout << getName() << " doesn't have the property: " << property;
    std::cout << ", or it is mortgaged already." << std::endl;
}

// void Player::unmortgage(const std::string &property) will try to mortgage
//   the given property
void Player::unmortgage(const std::string &property) {
    for (int i = 0; i < (int)mortgagedList.size(); i += 1) {
        if (mortgagedList.at(i)->getName() == property) {
            int payment = mortgagedList.at(i)->getPrice() * 0.6;
            if (getCash() < payment) {
                std::cout << "You don't have enough money for unmortgaging ";
                std::cout << "this building." << std::endl;
                return;
            }
            pay(payment);
	    ownedList.emplace_back(mortgagedList.at(i));
	    mortgagedList.at(i)->setImprovmentLevel(0);
            std::cout << mortgagedList.at(i)->getName() << " is unmortgaged from the bank." << std::endl;
            mortgagedList.erase(mortgagedList.begin() + i);
            return;
        }
    }
    std::cout << getName() << " doesn't have the property: " << property;
    std::cout << ", or it is unmortgaged already." << std::endl;
}


// void Player::tradeWith(...) will try to trade the target player.
// This function has three overloading form:
//   1. void tradeWith(playerPtr, const int &, const std::string &)
//   2. void tradeWith(playerPtr, const std::string &, const int &)
//   3. void tradeWith(playerPtr, const std::string &, const std::string &)
void Player::tradeWith(Player *trader, const int &money,
                       const std::string &receive) {
    if (getCash() < money) {
        std::cout << "Sorry, you don't have so much money for this trade." << std::endl;
        return;
    }
    if (trader == BANK) {
        std::cout << "Sorry, you cannot trade with bank or somebody we don't know" << std::endl;
        return;
    }
    Ownable *result = trader->tradeAgree(money, receive);
    if (result) {
        pay(money);
        ownedList.emplace_back(result);
        result->setOwner(this);
        std::cout << "The trade is made. Congratulations." << std::endl;
    } else {
        std::cout << "The trade is cancelled." << std::endl;
    }
}


void Player::tradeWith(Player *trader, const std::string &give, const int &money) {
    if (trader == BANK) {
        std::cout << "Sorry, you cannot trade with bank or somebody we don't know" << std::endl;
        return;
    }
    Ownable *property = nullptr;
    for (int i = 0; i < (int)ownedList.size(); i += 1) {
        if (ownedList.at(i)->getName() == give) {
            property = ownedList.at(i);
        }
    }
    if (!property) {
        std::cout << "Sorry, you don't have this building: " << give << std::endl;
        return;
    }
    if (property->getImproveLevel()) {
        std::cout << "Sorry, " << "this building cannot be sold." << std::endl;
        std::cout << "The improvement level of this building is: " << property->getImproveLevel() << std::endl;
        return;
    }
    if (property->checkOtherImprove()) {
        std::cout << "Sorry, " << "this building cannot be sold." << std::endl;
        std::cout << "This building is under monopoly, and some of its monopoly building is improved." << std::endl;
        return;
    }
    bool result = trader->tradeAgree(property, money);
    if (result) {
        for (int i = 0; i < (int)ownedList.size(); i += 1) {
            if (ownedList.at(i) == property) {
                ownedList.erase(ownedList.begin() + i);
            }
        }
        pay(-1 * money);
        std::cout << "The trade is made. Congratulations." << std::endl;
    } else {
        std::cout << "The trade is cancelled." << std::endl;
    }
}


void Player::tradeWith(Player *trader, const std::string &give, const std::string &receive) {
    if (trader == BANK) {
        std::cout << "Sorry, you cannot trade with bank or somebody we don't know" << std::endl;
        return;
    }
    Ownable *property = nullptr;
    for (int i = 0; i < (int)ownedList.size(); i += 1) {
        if (ownedList.at(i)->getName() == give) {
            property = ownedList.at(i);
        }
    }
    if (!property) {
        std::cout << "Sorry, you don't have this building: " << give << std::endl;
        return;
    }
    if (property->getImproveLevel()) {
        std::cout << "Sorry, " << "this building cannot be sold." << std::endl;
        std::cout << "The improvement level of this building is: " << property->getImproveLevel() << std::endl;
        return;
    }
    if (property->checkOtherImprove()) {
        std::cout << "Sorry, " << "this building cannot be sold." << std::endl;
        std::cout << "This building is under monopoly, and some of its monopoly building is improved." << std::endl;
        return;
    }
    Ownable *result = trader->tradeAgree(property, receive);
    if (result) {
        for (int i = 0; i < (int)ownedList.size(); i += 1) {
            if (ownedList.at(i) == property) {
                ownedList.erase(ownedList.begin() + i);
            }
        }
        ownedList.emplace_back(result);
        result->setOwner(this);
        std::cout << "The trade is made. Congratulations." << std::endl;
    } else {
        std::cout << "The trade is cancelled." << std::endl;
    }
}



// Player::tradeAgree(...) will check the agreement and return the result
//   of the trader
// This function has three overloading form:
//   1. ownablePtr tradeAgree(const int, const std::string);
//   2. const bool tradeAgree(ownablePtr, const int);
//   3. ownablePtr tradeAgree(ownablePtr, const std::string);
Ownable *Player::tradeAgree(const int money, const std::string receive) {
    Ownable *property = nullptr;
    for (int i = 0; i < (int)ownedList.size(); i += 1) {
        if (ownedList.at(i)->getName() == receive) {
            property = ownedList.at(i);
        }
    }
    if (!property) {
        std::cout << "Sorry, " << getName() << " does not have property: " << receive << std::endl;
        return nullptr;
    }
    if (property->getImproveLevel()) {
        std::cout << "Sorry, " << "this building cannot be sold." << std::endl;
        std::cout << "The improvement level of this building is: " << property->getImproveLevel() << std::endl;
        return nullptr;
    }
    if (property->checkOtherImprove()) {
        std::cout << "Sorry, " << "this building cannot be sold." << std::endl;
        std::cout << "This building is under monopoly, and some of its monopoly building is improved." << std::endl;
        return nullptr;
    }
    std::cout << "Do you want to trade $" << money << " with your property: " << receive << "?" << std::endl;
    std::cout << "Type accept if you want, type reject is you don't" << std::endl;
    std::string choose = "";
    while (true) {
        std::cin >> choose;
        if (std::cin.good()) {
            if (choose == "accept") {
                for (int i = 0; i < (int)ownedList.size(); i += 1) {
                    if (ownedList.at(i)->getName() == receive) {
                        ownedList.erase(ownedList.begin() + i);
                    }
                }
                pay(-1 * money);
                return property;
            } else if (choose == "reject") {
                std::cout << "Ok, maybe next time~" << std::endl;
                return nullptr;
            } else {
                std::cout << "You should type accept or reject" << std::endl;
            }
        } else {
            std::cin.ignore();
            std::cin.clear();
        }
    }
}


const bool Player::tradeAgree(Ownable *property, const int money) {
    if (getCash() < money) {
        std::cout << "Sorry, you don't have so much money for this trade." << std::endl;
        return false;
    }
    std::string choose = "";
    std::cout << "Do you want to trade " << property->getName() << " with $" << money << "?" << std::endl;
    std::cout << "Type accept if you want, type reject is you don't" << std::endl;
    while (true) {
        std::cin >> choose;
        if (std::cin.good()) {
            if (choose == "accept") {
                pay(money);
                ownedList.emplace_back(property);
                property->setOwner(this);
                return true;
            } else if (choose == "reject") {
                std::cout << "Ok, maybe next time~" << std::endl;
                return false;
            } else {
                std::cout << "You should type accept or reject" << std::endl;
            }
        } else {
            std::cin.ignore();
            std::cin.clear();
        }
    }
}


Ownable *Player::tradeAgree(Ownable *property, const std::string receive) {
    Ownable *p = nullptr;
    for (int i = 0; i < (int)ownedList.size(); i += 1) {
        if (ownedList.at(i)->getName() == receive) {
            p = ownedList.at(i);
        }
    }
    if (!p) {
        std::cout << "Sorry, " << getName() << " does not have property: " << receive << std::endl;
        return nullptr;
    }
    if (p->getImproveLevel()) {
        std::cout << "Sorry, " << "this building cannot be sold." << std::endl;
        std::cout << "The improvement level of this building is: " << property->getImproveLevel() << std::endl;
        return nullptr;
    }
    if (p->checkOtherImprove()) {
        std::cout << "Sorry, " << "this building cannot be sold." << std::endl;
        std::cout << "This building is under monopoly, and some of its monopoly building is improved." << std::endl;
        return nullptr;
    }
    std::cout << "Do you want to trade " << property->getName() << " with your property: " << receive << "?" << std::endl;
    std::cout << "Type accept if you want, type reject is you don't" << std::endl;
    std::string choose = "";
    while (true) {
        std::cin >> choose;
        if (std::cin.good()) {
            if (choose == "accept") {
                for (int i = 0; i < (int)ownedList.size(); i += 1) {
                    if (ownedList.at(i) == p) {
                        ownedList.erase(ownedList.begin() + i);
                    }
                }
                ownedList.emplace_back(property);
                property->setOwner(this);
                return p;
            } else if (choose == "reject") {
                std::cout << "Ok, maybe next time~" << std::endl;
                return nullptr;
            } else {
                std::cout << "You should type accept or reject" << std::endl;
            }
        } else {
            std::cin.ignore();
            std::cin.clear();
        }
    }
}


// void Player::showAssets(void) will show all the assests that the player
//   currently has.
void Player::showAssets(void) {
    std::cout << "Player: " << getName() << std::endl;
    std::cout << "- CashFlow: " << getCash() << std::endl;
    std::cout << "- Cup:" << getCup() << std::endl;
    std::cout << "- Owned List: " << std::endl;
    for (int i = 0; i < (int)ownedList.size(); i += 1) {
        std::cout << "  " << (i + 1) << ". " << ownedList.at(i)->getName();
        std::cout << " " << ownedList.at(i)->getImproveLevel() << std::endl;
    }
    std::cout << "- Mortgaged List: " << std::endl;
    for (int i = 0; i < (int)mortgagedList.size(); i += 1) {
        std::cout << "  " << i << ". " << mortgagedList.at(i)->getName();
        std::cout << " " << -1 << std::endl;
    }
}


// void Player::takeTuition(const int money, ownablePtr property) will take the
//   tuition from the owned property.
void Player::takeTuition(const int money, Ownable *property) {
    bool ownedProperty = true;
    for (int i = 0; i < (int)mortgagedList.size(); i += 1) {
        if (mortgagedList.at(i) == property) {
            ownedProperty = false;
            break;
        }
    }
    int payment = money;
    if (!ownedProperty) { payment /= 2; }
    pay(-1 * payment);
}


// void Player::destroy(void) will destory all data for avoiding
//   memory leak.
void Player::destroy(void) {
    for (int i = 0; i < (int)ownedList.size(); i += 1) {
        ownedList.at(i) = nullptr;
    }
    for (int i = 0; i < (int)mortgagedList.size(); i += 1) {
        mortgagedList.at(i) = nullptr;
    }
    landing = nullptr;
    lastPropertyOwner = nullptr;
}


// const int Player::getTotalWorth(void) const will return the total worth that
//   the player currently has.
// Note including player's savings, printed prices of all buildings
//   player owns, and costs of each improvement
const int Player::getTotalWorth(void) const {
    int worth = getCash();
    for (int i = 0; i < (int)ownedList.size(); i += 1) {
        worth += ownedList.at(i)->getTotalCost();
    }
    for (int i = 0; i <(int)mortgagedList.size(); i += 1) {
        worth += (mortgagedList.at(i)->getTotalCost() / 2);
    }
    return worth;
}


// const bool Player::checkMortgage(Ownable *) will return true if the property
//   is mortgaged.
const bool Player::checkMortgage(Ownable *p) {
    for (int i = 0; i < (int)mortgagedList.size(); i += 1) {
        if (p == mortgagedList.at(i)) {
            return true;
        }
    }
    return false;
}


// void Player::turnPublic(void) will turn every player's property into the market.
void Player::turnPublic(void) {
    for (int i = 0; i < (int)ownedList.size(); i += 1) {
        ownedList.at(i)->setOwner(nullptr);
    }
    for (int i = 0; i < (int)mortgagedList.size(); i += 1) {
        mortgagedList.at(i)->setOwner(nullptr);
    }
    for (int i = 0; i < (int)ownedList.size(); i += 1) {
        ownedList.erase(ownedList.begin());
    }
    for (int i = 0; i < (int)mortgagedList.size(); i += 1) {
        mortgagedList.erase(ownedList.begin());
    }
}


// void Player::turnPrivate(Player *player) will turn every player's property to
//   a private player.
void Player::turnPrivate(Player *player) {
    for (int i = 0; i < (int)ownedList.size(); i += 1) {
        ownedList.at(i)->setOwner(player);
        player->receiveOwned(ownedList.at(i));
    }
    for (int i = 0; i < (int)mortgagedList.size(); i += 1) {
        mortgagedList.at(i)->setOwner(player);
        player->pay(mortgagedList.at(i)->getPrice() / 10);
    }
    std::cout << "Do you want to unmortgage the mortgagedList from " << getName() << " now?" << std::endl;
    std::cout << "Type Y if you want, type N is you don't." << std::endl;
    char choose = 'N';
    while (true) {
        std::cin >> choose;
        if (std::cin.good()) {
            if (choose == 'Y') {
                for (int i = 0; i < (int)mortgagedList.size(); i += 1) {
                    mortgagedList.at(i)->setOwner(player);
                    player->pay(mortgagedList.at(i)->getPrice() / 2);
                    player->receiveOwned(mortgagedList.at(i));
                }
                break;
            } else if (choose == 'N') {
                for (int i = 0; i < (int)mortgagedList.size(); i += 1) {
                    player->receiveMortgaged(mortgagedList.at(i));
                }
                std::cout << "Ok, maybe next time~" << std::endl;
                break;
            } else {
                std::cout << "You should type \'Y\' or \'N\'" << std::endl;
            }
        } else {
            std::cin.ignore();
            std::cin.clear();
        }
    }
    for (int i = 0; i < (int)ownedList.size(); i += 1) {
        ownedList.erase(ownedList.begin());
    }
    for (int i = 0; i < (int)mortgagedList.size(); i += 1) {
        mortgagedList.erase(ownedList.begin());
    }
}


// void Player::receiveOwned(Ownable *) will receive the ownable building like the player
//   ownes.
void Player::receiveOwned(Ownable *property) {
    ownedList.emplace_back(property);
}


// void Player::receiveMortgaged(Ownable *) will receive the ownable building like
//   the player mortgaged this building.
void Player::receiveMortgaged(Ownable *property) {
    mortgagedList.emplace_back(property);
}
