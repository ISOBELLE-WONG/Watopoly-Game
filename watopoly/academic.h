#ifndef __ACADEMIC_H__
#define __ACADEMIC_H__


#include <string>
#include <vector>
#include "ownable.h"
#include "player.h"


class Academic;
struct PayList;


typedef PayList pl;
typedef std::shared_ptr<Academic> acadPtr;


struct PayList {
    PayList() { data.clear(); }
    // Constructor of PayList;
    PayList(int ic, int l0, int l1, int l2, int l3, int l4, int l5):
        improveCost{ic} {
            data.emplace_back(l0);
            data.emplace_back(l1);
            data.emplace_back(l2);
            data.emplace_back(l3);
            data.emplace_back(l4);
            data.emplace_back(l5);
    }
    
    // Public fields
    int improveCost = 0;
    std::vector<int> data;
};



class Academic: public Ownable {
protected:
    int improveLevel = 0;
public:
    pl payList;
    
    // Constructor of Academic
    explicit Academic(const std::string &, const std::string &, const int &,
            const pl &);
    
    // virtual const int getTotalCost(void) will return the total cost that
    //   the player has paid for the property
    virtual const int getTotalCost(void) override;
    
    // const int getTuition(playerPtr p) will return the amount
    //   of money that the player should pay.
    virtual const int getTuition(Player &) override;
    
    // void improve(void) will improve the property.
    virtual void improve(void) override;
    
    // void degenerate(void) will degenerate the property.
    virtual void degenerate(void) override;
    
    // void setImprovmentLevel(const int) will set the
    //   improvement level directly
    virtual void setImprovmentLevel(const int) override;
    
    // const int getImproveLevel(void) will return the
    //   improvement level that the current building has.
    virtual const int getImproveLevel(void) override;
    
    // const bool checkOtherImprove(void) will return true if
    //   the property in the same monopoly set is improved.
    //   This function will return false otherwise.
    virtual const bool checkOtherImprove(void) override;
    
    // Destructor of Academic
    virtual ~Academic();
};



#endif
