#ifndef __GRID_H__
#define __GRID_H__

#include <iostream>
#include <memory>
#include <vector>
#include <iomanip>
#include "player.h"
#include "osap.h"
#include "academic.h"
#include "residence.h"
#include "gym.h"
#include "slc.h"
#include "tuition.h"
#include "needleshall.h"
#include "goose.h"
#include "coopfee.h"
#include "dctims.h"
#include "gotims.h"


class Grid;
class Property;


typedef std::shared_ptr<Grid> gridPtr;
typedef std::shared_ptr<Property> propertyPtr;


class Grid {
    bool seedPermit = false;
    int seed = 0;
    std::vector<propertyPtr> map;
    
    // void gridInit(void) will initialize the whole map.
    void gridInit(void);
public:
    // Constructor of Grid
    explicit Grid(const int);
    
    // void Attach(void) will set all next and prev value
    //   to each cell.
    void gridAttach(void);
    
    // void gridClean(void) will clean the whole map and prevent the
    //   situation like memory leak.
    void gridClean(void);
    
    // void gridPrint(void) will print the current map.
    void gridPrint(void);
    
    // void gridSave(std::ostream &) will save all the information
    //   in the whole grid.
    void gridSave(std::ostream &);
    
    // propertyPtr at(const int &) will return the pointer at the
    //   position, it will return nullptr if this is not a valid
    //   position.
    propertyPtr at(const int &);
    
    // propertyPtr find(std::string &) will return the pointer of
    //   the first property with the matched name in the map. If there is
    //   no such property, then return nullptr.
    propertyPtr find(std::string &);
    
    // void setSeed(const int ) will set a new seed to the grid
    void setSeed(const int );
    
    // const int getLen(void) will return the len of the map.
    const int getLen(void);

    // const int findPos(const std::string name) will return the position
    //   of the given property
    const int findPos(const std::string name);

    // Destructor of Grid
    ~Grid();


};

#endif

