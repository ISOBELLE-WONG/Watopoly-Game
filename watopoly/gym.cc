#include "gym.h"


// Constructor of Gym
Gym::Gym(const std::string &name, const std::string &type, const int &purchaseCost,
         const int seed, const bool seedPermit): Ownable(name, type, true, false, purchaseCost), seed(seed), seedPermit(seedPermit) { }


// const int getTotalCost(void) will return the total cost that
//   the player has paid for the property
const int Gym::getTotalCost(void) { return purchaseCost; }


// const int Gym::getTuition(playerPtr p) will return the amount
//   of money that the player should pay.
const int Gym::getTuition(Player &p) {
    if (!getOwner()) { return 0; }
    if (checkMortgage()) { return 0; }
    int time = 4;
    for (int i = 0; i < (int)monopolyList.size(); i += 1) {
        if (monopolyList.at(i)->getOwner() == getOwner()) {
            time = 10;
        }
    }
    int roll = 0, result = 0;
    if (!seedPermit) {
        seed = (int)std::chrono::system_clock::now().time_since_epoch().count();
    }
    std::default_random_engine rng{(unsigned)seed};
    std::shuffle(playRoll.begin(), playRoll.end(), rng);
    roll = *playRoll.begin();
    result += roll;
    std::cout << "The first roll is " << roll << std::endl;
    std::shuffle(playRoll.begin(), playRoll.end(), rng);
    roll = *playRoll.begin();
    result += roll;
    std::cout << "The second roll is " << roll << std::endl;
    return result * time;
}


// void Gym::improve(void) will improve the property.
void Gym::improve(void) {
    std::cout << "Sorry, this building is not improvable." << std::endl;
}


// void degenerate(void) will degenerate the property.
void Gym::degenerate(void) {
    std::cout << "Sorry, this building is not degeneratable." << std::endl;
}


// void Gym::setImprovmentLevel(const int level) will set the
//   improvement level directly
void Gym::setImprovmentLevel(const int level) { return; }


// const bool Gym::checkOtherImprove(void) will return true if
//   the property in the same monopoly set is improved.
//   This function will return false otherwise.
const bool Gym::checkOtherImprove(void) { return false; }


// Destructor of Gym
Gym::~Gym() { }
