#ifndef __GYM_H__
#define __GYM_H__


#include <algorithm>
#include <chrono>
#include <memory>
#include <random>
#include <string>
#include "player.h"
#include "ownable.h"


class Gym;


typedef std::shared_ptr<Gym> gymPtr;


class Gym: public Ownable {
protected:
    std::vector<int> playRoll = {1, 2, 3, 4, 5, 6};
    int seed;
    const bool seedPermit;
public:
    // Constructor of Gym
    explicit Gym(const std::string &, const std::string &, const int &, const int, const bool);
    
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
    
    // Destructor of Gym
    virtual ~Gym();
};


#endif
