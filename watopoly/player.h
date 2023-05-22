#ifndef __PLAYER_H__
#define __PLAYER_H__


#include <memory>
#include <string>
#include <vector>
#include <iostream>
#include "ownable.h"
#include "property.h"


class Player;
class Ownable;
class Property;


typedef std::shared_ptr<Property> propertyPtr;
typedef std::shared_ptr<Ownable> ownablePtr;
typedef std::shared_ptr<Player> playerPtr;


class Player {
    int cup = 0;
    int cashFlow = 1500;
    bool movable = true;
    bool meet_OSAP = false;
    const char symbol;
    const std::string name;
    Property *landing;
    std::vector<Ownable *> ownedList;
    std::vector<Ownable *> mortgagedList;
    
public:
    Player *lastPropertyOwner = nullptr;
    int moneyOwned = 0;
    bool movalready = false;
    
    // Constructor of Player
    explicit Player(Property *, const char &, const std::string &);
    
    // const int &getCup(void) will return the number of the cups that
    //   the current player holds.
    const int &getCup(void);
    
    // void addCup(const int) will add the number of cups to the original
    //   number of cup.
    void addCup(const int num);
    
    // const int &getCash(void) will return the current cash that
    //   the player has.
    const int &getCash(void) const;
    
    // const bool &getMovable(void) will return true if the object of the
    //   Player is movable, false otherwise.
    const bool &getMovable(void);
    
    // const std::string &getSymbol(void) will return the symbol of the
    //   current object of player.
    const char &getSymbol(void);
    
    // const std::string &getName(void) will return the name of the
    //   current object of Player
    const std::string &getName(void);
    
    // propertyPtr getLanding(void) will return the landing address.
    Property *getLanding(void);
    
    // void move(const int &) will control the object of the Player
    //   move the number of given steps.
    // Note that the object of the Player will be unmovable!
    void move(const int &);
    
    // void move(const std::string &) will control the object of the Player
    //   move to the given position.
    // Note that the object of the Player will be unmovable!
    void move(const std::string &);
    
    // void moveReset(void) will reset the object of the Player to be
    //   movable.
    void moveReset(void);
    
    // void makeAction(void) will make action to the landing property.
    void makeAction(void);
    
    // void pay(const int) will make the plater pay the give tuition.
    void pay(const int);
    
    // void payDebt(void) will try to pay the owned money.
    void payDebt(void);
    
    // void buy(ownablePtr) will make the player buy the
    //   give building.
    void buy(Ownable *);
    
    // void get(ownablePtr) will make the player get the building
    //   without any cost.
    void get(Ownable *);
    
    // void improve(const std::string &) will try to improve the
    //   given property
    void improve(const std::string &);
    
    // void degenerate(const std::string &) will try to degenerate
    //   the give property
    void degenerate(const std::string &);
    
    // void mortgage(const std::string &) will try to mortgage
    //   the given property
    void mortgage(const std::string &);
    
    // void unmortgage(const std::string &) will try to mortgage
    //   the given property
    void unmortgage(const std::string &);
    
    // void tradeWith(...) will try to trade the target player.
    // This function has three overloading form:
    //   1. void tradeWith(playerPtr, const int &, const std::string &)
    //   2. void tradeWith(playerPtr, const std::string &, const int &)
    //   3. void tradeWith(playerPtr, const std::string &, const std::string &)
    void tradeWith(Player *, const int &, const std::string &);
    void tradeWith(Player *, const std::string &, const int &);
    void tradeWith(Player *, const std::string &, const std::string &);
    
    // tradeAgree(...) will check the agreement and return the result
    //   of the trader
    // This function has three overloading form:
    //   1. ownablePtr tradeAgree(const int, const std::string);
    //   2. const bool tradeAgree(ownablePtr, const int);
    //   3. ownablePtr tradeAgree(ownablePtr, const std::string);
    Ownable *tradeAgree(const int, const std::string);
    const bool tradeAgree(Ownable *, const int);
    Ownable *tradeAgree(Ownable *, const std::string);
    
    // void showAssets(void) will show all the assests that the player
    //   currently has.
    void showAssets(void);
    
    // void takeTuition(const int, ownablePtr) will take the
    //   tuition from the owned property.
    void takeTuition(const int, Ownable *);
    
    // void destroy(void) will destory all data for avoiding
    //   memory leak.
    void destroy(void);
    
    // const int getTotalWorth(void) const will return the total worth that
    //   the player currently has.
    // Note including player's savings, printed prices of all buildings
    //   player owns, and costs of each improvement
    const int getTotalWorth(void) const;
    
    // const bool checkMortgage(Ownable *) will return true if the property
    //   is mortgaged.
    const bool checkMortgage(Ownable *);
    
    // void turnPublic(void) will turn every player's property into the market.
    void turnPublic(void);
    
    // void turnPrivate(Player *) will turn every player's property to
    //   a private player.
    void turnPrivate(Player *);
    
    // void receiveOwned(Ownable *) will receive the ownable building like the player
    //   ownes.
    void receiveOwned(Ownable *);
    
    // void receiveMortgaged(Ownable *) will receive the ownable building like
    //   the player mortgaged this building.
    void receiveMortgaged(Ownable *);
    
    ~Player() {
	destroy();
        std::cout << name << " leaves the game!" << std::endl;
    }
};


#endif
