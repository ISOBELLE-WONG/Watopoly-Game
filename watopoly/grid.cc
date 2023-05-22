#include "grid.h"


// void Grid::gridInit(void) will initialize the whole map.
void Grid::gridInit(void) {
    std::cout << "The grid is initialized ..." << std::endl;
    map.emplace_back(OSAPPtr(new OSAP()));
    map.emplace_back(acadPtr(new Academic("AL", "Art1", 40, pl{50, 2, 10, 30, 90, 160, 250})));
    map.emplace_back(SLCPtr(new SLC()));
    map.emplace_back(acadPtr(new Academic("ML", "Art1", 60, pl{50, 4, 10, 30, 90, 160, 250})));
    map.emplace_back(tuitPtr(new Tuition()));
    map.emplace_back(resiPtr(new Residence("MKV", "Residence", 200)));
    map.emplace_back(acadPtr(new Academic("ECH", "Art2", 100, pl{50, 6, 30, 90, 270, 400, 550})));
    map.emplace_back(needPtr(new NeedlesHall()));
    map.emplace_back(acadPtr(new Academic("PAS", "Art2", 100, pl{50, 6, 30, 90, 270, 400, 550})));
    map.emplace_back(acadPtr(new Academic("HH", "Art2", 120, pl{50, 8, 40, 100, 300, 450, 600})));
    map.emplace_back(DCTPtr(new DCTims()));
    map.emplace_back(acadPtr(new Academic("RCH", "ENG", 140, pl{100, 10, 50, 150, 450, 625, 750})));
    map.emplace_back(gymPtr(new Gym("PAC", "Gym", 200, seed, seedPermit)));
    map.emplace_back(acadPtr(new Academic("DWE", "ENG", 140, pl{100, 10, 50, 150, 450, 625, 750})));
    map.emplace_back(acadPtr(new Academic("CPH", "ENG", 160, pl{100, 12, 60, 180, 500, 700, 900})));
    map.emplace_back(resiPtr(new Residence("UWP", "Residence", 200)));
    map.emplace_back(acadPtr(new Academic("LHI", "Health", 180, pl{100, 14, 70, 200, 550, 750, 950})));
    map.emplace_back(SLCPtr(new SLC()));
    map.emplace_back(acadPtr(new Academic("BMH", "Health", 180, pl{100, 14, 70, 200, 550, 750, 950})));
    map.emplace_back(acadPtr(new Academic("OPT", "Health", 200, pl{100, 16, 80, 220, 600, 800, 1000})));
    map.emplace_back(gooPtr(new Goose()));
    map.emplace_back(acadPtr(new Academic("EV1", "ENV", 220, pl{150, 18, 90, 250, 700, 875, 1050})));
    map.emplace_back(needPtr(new NeedlesHall()));
    map.emplace_back(acadPtr(new Academic("EV2", "ENV", 220, pl{150, 18, 90, 250, 700, 875, 1050})));
    map.emplace_back(acadPtr(new Academic("EV3", "ENV", 240, pl{150, 20, 100, 300, 750, 925, 1100})));
    map.emplace_back(resiPtr(new Residence("V1", "Residence", 200)));
    map.emplace_back(acadPtr(new Academic("PHYS", "Sci1", 260, pl{150, 22, 110, 330, 800, 975, 1150})));
    map.emplace_back(acadPtr(new Academic("B1", "Sci1", 260, pl{150, 22, 110, 330, 800, 975, 1150})));
    map.emplace_back(gymPtr(new Gym("CIF", "Gym", 200, seed, seedPermit)));
    map.emplace_back(acadPtr(new Academic("B2", "Sci1", 280, pl{150, 24, 120, 360, 850, 1025, 1200})));
    map.emplace_back(goPtr(new GoTims()));
    map.emplace_back(acadPtr(new Academic("EIT", "Sci2", 300, pl{200, 26, 130, 390, 900, 1100, 1275})));
    map.emplace_back(acadPtr(new Academic("ESC", "Sci2", 300, pl{200, 26, 130, 390, 900, 1100, 1275})));
    map.emplace_back(SLCPtr(new SLC()));
    map.emplace_back(acadPtr(new Academic("C2", "Sci2", 320, pl{200, 28, 150, 450, 1000, 1200, 1400})));
    map.emplace_back(resiPtr(new Residence("REV", "Residence", 200)));
    map.emplace_back(needPtr(new NeedlesHall()));
    map.emplace_back(acadPtr(new Academic("MC", "Math", 350, pl{200, 35, 175, 500, 1100, 1300, 1500})));
    map.emplace_back(coopPtr(new CoopFee()));
    map.emplace_back(acadPtr(new Academic("DC", "Math", 400, pl{200, 50, 200, 600, 1400, 1700, 2000})));
}


// Constructor of Grid
Grid::Grid(const int seed): seed(seed) { gridInit(); }


// void Grid::gridAttach(void) will set all next and prev value
//   to each cell.
void Grid::gridAttach(void) {
    int next, prev;
    for (int i = 0; i < (int)map.size(); i += 1) {
        next = (i + 1) % (int)map.size();
        prev = (i - 1 + (int)map.size()) % (int)map.size();
        map[i]->setNext((map[next]).get());
        map[i]->setPrev((map[prev]).get());
    }
    for (int i = 0; i < (int)map.size(); i += 1) {
        if (map.at(i)->getType() == "EVENT") { continue; }
        for (int j = 0; j < (int)map.size(); j += 1) {
            if (i == j) { continue; }
            if (map.at(i)->getType() == map.at(j)->getType()) {
                map.at(i)->attachMonopoly(map.at(j).get());
            }
        }
    }
}


// void Grid::gridClean(void) will clean the whole map and prevent the
//   situation like memory leak.
void Grid::gridClean(void) {
    for (int i = 0; i < (int)map.size(); i += 1) {
        map.at(i)->destroy();
    }
}


// void Grid::gridPrint(void) will print the current map.
void Grid::gridPrint(void) {
    std::cout << "________________________________________";
    std::cout << "_________________________________________________" << std::endl;
    
    for (int i = 20; i < 31; i += 1) {
        std::string name = map.at(i)->getName();
        if (name == "Goose Nesting") {
            std::cout << "|Goose  ";
        } else if (name == "Needles Hall") {
            std::cout << "|NEEDLES";
        } else if (name == "V1") {
            std::cout << "|V1     ";
        } else if (name == "CIF") {
            std::cout << "|CIF    ";
        } else if (name == "Go to Tims") {
            std::cout << "|GO TO  ";
        } else {
            std::cout << "|";
            if (map.at(i)->getImproveLevel() == 0) {
                std::cout << "       ";
            } else if (map.at(i)->getImproveLevel() == -1) {
                std::cout << "-1     ";
            } else {
                std::cout << map.at(i)->getImproveLevel();
                std::cout << "      ";
            }
        }
    }
    std::cout << "|" << std::endl;
    
    for (int i = 20; i < 31; i += 1) {
        std::string name = map.at(i)->getName();
        if (name == "Goose Nesting") {
            std::cout << "|Nesting";
        } else if (name == "Needles Hall") {
            std::cout << "|HALL   ";
        } else if (name == "V1" || name == "CIF") {
            std::cout << "|       ";
        } else if (name == "Go to Tims") {
            std::cout << "|TIMS   ";
        } else {
            std::cout << "|-------";
        }
    }
    std::cout << "|" << std::endl;
    
    for (int i = 20; i < 31; i += 1) {
        std::string name = map.at(i)->getName();
        if (name == "Goose Nesting" || name == "Needles Hall") {
            std::cout << "|       ";
        } else if (name == "V1" || name == "CIF" || name == "Go to Tims") {
            std::cout << "|       ";
        } else {
            std::cout << "|" << std::setw(7) << std::setfill(' ') << std::left << map.at(i)->getName();
        }
    }
    std::cout << "|" << std::endl;
    
    for (int i = 20; i < 31; i += 1) {
        std::cout << "|" << std::setw(7) << std::setfill(' ') << std::left << map.at(i)->getGuest();
    }
    std::cout << "|" << std::endl;
    
    for (int i = 20; i < 31; i += 1) {
        std::cout << "|_______";
    }
    std::cout << "|" << std::endl;
    
    std::cout << "|";
    if (map.at(19)->getImproveLevel() == 0) {
        std::cout << "       ";
    } else if (map.at(19)->getImproveLevel() == -1) {
        std::cout << "-1     ";
    } else {
        std::cout << map.at(19)->getImproveLevel();
        std::cout << "      ";
    }
    std::cout << "|                                                                       ";
    std::cout << "|";
    if (map.at(31)->getImproveLevel() == 0) {
        std::cout << "       ";
    } else if (map.at(31)->getImproveLevel() == -1) {
        std::cout << "-1     ";
    } else {
        std::cout << map.at(31)->getImproveLevel();
        std::cout << "      ";
    }
    std::cout << "|" << std::endl;
    
    std::cout << "|-------|                                                                       |-------|" << std::endl;
    
    std::cout << "|" << std::setw(7) << std::setfill(' ') << std::left << map.at(19)->getName();
    std::cout << "|                                                                       ";
    std::cout << "|" << std::setw(7) << std::setfill(' ') << std::left << map.at(31)->getName();
    std::cout << "|" << std::endl;
    
    std::cout << "|" << std::setw(7) << std::setfill(' ') << std::left << map.at(19)->getGuest();
    std::cout << "|                                                                       ";
    std::cout << "|" << std::setw(7) << std::setfill(' ') << std::left << map.at(31)->getGuest();
    std::cout << "|" << std::endl;
    
    std::cout << "|_______";
    std::cout << "|                                                                       ";
    std::cout << "|_______|" << std::endl;
    
    std::cout << "|";
    if (map.at(18)->getImproveLevel() == 0) {
        std::cout << "       ";
    } else if (map.at(18)->getImproveLevel() == -1) {
        std::cout << "-1     ";
    } else {
        std::cout << map.at(18)->getImproveLevel();
        std::cout << "      ";
    }
    std::cout << "|                                                                       ";
    std::cout << "|";
    if (map.at(32)->getImproveLevel() == 0) {
        std::cout << "       ";
    } else if (map.at(32)->getImproveLevel() == -1) {
        std::cout << "-1     ";
    } else {
        std::cout << map.at(32)->getImproveLevel();
        std::cout << "      ";
    }
    std::cout << "|" << std::endl;
    
    std::cout << "|-------|                                                                       |-------|" << std::endl;
    
    std::cout << "|" << std::setw(7) << std::setfill(' ') << std::left << map.at(18)->getName();
    std::cout << "|                                                                       ";
    std::cout << "|" << std::setw(7) << std::setfill(' ') << std::left << map.at(32)->getName();
    std::cout << "|" << std::endl;
    
    std::cout << "|" << std::setw(7) << std::setfill(' ') << std::left << map.at(18)->getGuest();
    std::cout << "|                                                                       ";
    std::cout << "|" << std::setw(7) << std::setfill(' ') << std::left << map.at(32)->getGuest();
    std::cout << "|" << std::endl;
    
    std::cout << "|_______";
    std::cout << "|                                                                       ";
    std::cout << "|_______|" << std::endl;
    
    std::cout << "|SLC    ";
    std::cout << "|                                                                       ";
    std::cout << "|SLC    ";
    std::cout << "|" << std::endl;
    
    std::cout << "|" << std::setw(7) << std::setfill(' ') << std::left << map.at(17)->getGuest();
    std::cout << "|                                                                       ";
    std::cout << "|" << std::setw(7) << std::setfill(' ') << std::left << map.at(33)->getGuest();
    std::cout << "|" << std::endl;
    
    std::cout << "|       ";
    std::cout << "|                                                                       ";
    std::cout << "|       |" << std::endl;
    
    std::cout << "|       ";
    std::cout << "|                                                                       ";
    std::cout << "|       |" << std::endl;
    
    std::cout << "|_______";
    std::cout << "|                                                                       ";
    std::cout << "|_______|" << std::endl;
    
    std::cout << "|";
    if (map.at(16)->getImproveLevel() == 0) {
        std::cout << "       ";
    } else if (map.at(16)->getImproveLevel() == -1) {
        std::cout << "-1     ";
    } else {
        std::cout << map.at(16)->getImproveLevel();
        std::cout << "      ";
    }
    std::cout << "|                                                                       ";
    std::cout << "|";
    if (map.at(34)->getImproveLevel() == 0) {
        std::cout << "       ";
    } else if (map.at(34)->getImproveLevel() == -1) {
        std::cout << "-1     ";
    } else {
        std::cout << map.at(34)->getImproveLevel();
        std::cout << "      ";
    }
    std::cout << "|" << std::endl;
    
    std::cout << "|-------|                                                                       |-------|" << std::endl;
    
    std::cout << "|" << std::setw(7) << std::setfill(' ') << std::left << map.at(16)->getName();
    std::cout << "|                                                                       ";
    std::cout << "|" << std::setw(7) << std::setfill(' ') << std::left << map.at(34)->getName();
    std::cout << "|" << std::endl;
    
    std::cout << "|" << std::setw(7) << std::setfill(' ') << std::left << map.at(16)->getGuest();
    std::cout << "|              _____________________________________________            ";
    std::cout << "|" << std::setw(7) << std::setfill(' ') << std::left << map.at(34)->getGuest();
    std::cout << "|" << std::endl;
    
    std::cout << "|_______";
    std::cout << "|             |                                             |           ";
    std::cout << "|_______|" << std::endl;
    
    std::cout << "|" << std::setw(7) << std::setfill(' ') << std::left << map.at(15)->getName();
    std::cout << "|             | #   #  ##  #####  ###  ###   ###  #   #   # |           ";
    std::cout << "|" << std::setw(7) << std::setfill(' ') << std::left << map.at(35)->getName();
    std::cout << "|" << std::endl;
    
    std::cout << "|" << std::setw(7) << std::setfill(' ') << std::left << map.at(15)->getGuest();
    std::cout << "|             | #   # #  #   #   #   # #  # #   # #   #   # |           ";
    std::cout << "|" << std::setw(7) << std::setfill(' ') << std::left << map.at(35)->getGuest();
    std::cout << "|" << std::endl;
    
    std::cout << "|       ";
    std::cout << "|             | # # # ####   #   #   # ###  #   # #    # #  |           ";
    std::cout << "|       |" << std::endl;
    
    std::cout << "|       ";
    std::cout << "|             | # # # #  #   #   #   # #    #   # #     #   |           ";
    std::cout << "|       |" << std::endl;
    
    std::cout << "|_______";
    std::cout << "|             | ##### #  #   #    ###  #     ###  ####  #   |           ";
    std::cout << "|_______|" << std::endl;
    
    std::cout << "|";
    if (map.at(14)->getImproveLevel() == 0) {
        std::cout << "       ";
    } else if (map.at(14)->getImproveLevel() == -1) {
        std::cout << "-1     ";
    } else {
        std::cout << map.at(14)->getImproveLevel();
        std::cout << "      ";
    }
    std::cout << "|             |_____________________________________________|           ";
    std::cout << "|NEEDLES|" << std::endl;
    
    std::cout << "|-------";
    std::cout << "|                                                                       ";
    std::cout << "|HALL   |" << std::endl;
    
    std::cout << "|" << std::setw(7) << std::setfill(' ') << std::left << map.at(14)->getName();
    std::cout << "|                                                                       ";
    std::cout << "|" << std::setw(7) << std::setfill(' ') << std::left << map.at(36)->getGuest();
    std::cout << "|" << std::endl;
    
    std::cout << "|" << std::setw(7) << std::setfill(' ') << std::left << map.at(14)->getGuest();
    std::cout << "|                                                                       ";
    std::cout << "|       |" << std::endl;
    
    std::cout << "|_______";
    std::cout << "|                                                                       ";
    std::cout << "|_______|" << std::endl;
    
    std::cout << "|";
    if (map.at(13)->getImproveLevel() == 0) {
        std::cout << "       ";
    } else if (map.at(13)->getImproveLevel() == -1) {
        std::cout << "-1     ";
    } else {
        std::cout << map.at(13)->getImproveLevel();
        std::cout << "      ";
    }
    std::cout << "|                                                                       ";
    std::cout << "|";
    if (map.at(37)->getImproveLevel() == 0) {
        std::cout << "       ";
    } else if (map.at(37)->getImproveLevel() == -1) {
        std::cout << "-1     ";
    } else {
        std::cout << map.at(37)->getImproveLevel();
        std::cout << "      ";
    }
    std::cout << "|" << std::endl;;
    
    std::cout << "|-------|                                                                       |-------|" << std::endl;
    
    std::cout << "|" << std::setw(7) << std::setfill(' ') << std::left << map.at(13)->getName();
    std::cout << "|                                                                       ";
    std::cout << "|" << std::setw(7) << std::setfill(' ') << std::left << map.at(37)->getName();
    std::cout << "|" << std::endl;
    
    std::cout << "|" << std::setw(7) << std::setfill(' ') << std::left << map.at(13)->getGuest();
    std::cout << "|                                                                       ";
    std::cout << "|" << std::setw(7) << std::setfill(' ') << std::left << map.at(37)->getGuest();
    std::cout << "|" << std::endl;
    
    std::cout << "|_______";
    std::cout << "|                                                                       ";
    std::cout << "|_______|" << std::endl;
    
    std::cout << "|PAC    ";
    std::cout << "|                                                                       ";
    std::cout << "|COOP   |" << std::endl;
    
    std::cout << "|" << std::setw(7) << std::setfill(' ') << std::left << map.at(12)->getGuest();
    std::cout << "|                                                                       ";
    std::cout << "|FEE    |" << std::endl;
    
    std::cout << "|       ";
    std::cout << "|                                                                       ";
    std::cout << "|" << std::setw(7) << std::setfill(' ') << std::left << map.at(38)->getGuest();
    std::cout << "|" << std::endl;
    
    std::cout << "|       ";
    std::cout << "|                                                                       ";
    std::cout << "|       |" << std::endl;
    
    std::cout << "|_______";
    std::cout << "|                                                                       ";
    std::cout << "|_______|" << std::endl;
    
    std::cout << "|";
    if (map.at(11)->getImproveLevel() == 0) {
        std::cout << "       ";
    } else if (map.at(11)->getImproveLevel() == -1) {
        std::cout << "-1     ";
    } else {
        std::cout << map.at(11)->getImproveLevel();
        std::cout << "      ";
    }
    std::cout << "|                                                                       ";
    std::cout << "|";
    if (map.at(39)->getImproveLevel() == 0) {
        std::cout << "       ";
    } else if (map.at(39)->getImproveLevel() == -1) {
        std::cout << "-1     ";
    } else {
        std::cout << map.at(39)->getImproveLevel();
        std::cout << "      ";
    }
    std::cout << "|" << std::endl;;
    
    std::cout << "|-------";
    std::cout << "|                                                                       ";
    std::cout << "|-------|" << std::endl;
    
    std::cout << "|" << std::setw(7) << std::setfill(' ') << std::left << map.at(11)->getName();
    std::cout << "|                                                                       ";
    std::cout << "|" << std::setw(7) << std::setfill(' ') << std::left << map.at(39)->getName();
    std::cout << "|" << std::endl;
    
    std::cout << "|" << std::setw(7) << std::setfill(' ') << std::left << map.at(11)->getGuest();
    std::cout << "|                                                                       ";
    std::cout << "|" << std::setw(7) << std::setfill(' ') << std::left << map.at(39)->getGuest();
    std::cout << "|" << std::endl;
    
    std::cout << "|_______";
    std::cout << "|_______";
    for (int i = 22; i < 30; i += 1) {
        std::cout << "________";
    }
    std::cout << "|_______";
    std::cout << "|" << std::endl;
    
    for (int i = 10; i >= 0; i -= 1) {
        std::string name = map.at(i)->getName();
        if (name == "DC Tims Line") {
            std::cout << "|DC Tims";
        } else if (name == "Needles Hall") {
            std::cout << "|NEEDLES";
        } else if (name == "MKV") {
            std::cout << "|MKV    ";
        } else if (name == "SLC") {
            std::cout << "|SLC    ";
        } else if (name == "Tuition") {
            std::cout << "|TUITION";
        } else if (name == "Collect OSAP") {
            std::cout << "|COLLECT";
        } else {
            std::cout << "|";
            if (map.at(i)->getImproveLevel() == 0) {
                std::cout << "       ";
            } else if (map.at(i)->getImproveLevel() == -1) {
                std::cout << "-1     ";
            } else {
                std::cout << map.at(i)->getImproveLevel();
                std::cout << "      ";
            }
        }
    }
    std::cout << "|" << std::endl;
    
    for (int i = 10; i >= 0; i -= 1) {
        std::string name = map.at(i)->getName();
        if (name == "DC Tims Line") {
            std::cout << "|Line   ";
        } else if (name == "Needles Hall") {
            std::cout << "|HALL   ";
        } else if (name == "MKV") {
            std::cout << "|" << std::setw(7) << std::setfill(' ') << std::left << map.at(5)->getGuest();
        } else if (name == "SLC") {
            std::cout << "|" << std::setw(7) << std::setfill(' ') << std::left << map.at(2)->getGuest();
        } else if (name == "Tuition") {
            std::cout << "|" << std::setw(7) << std::setfill(' ') << std::left << map.at(4)->getGuest();
        } else if (name == "Collect OSAP") {
            std::cout << "|OSAP   ";
        } else {
            std::cout << "|-------";
        }
    }
    std::cout << "|" << std::endl;
    
    for (int i = 10; i >= 0; i -= 1) {
        std::string name = map.at(i)->getName();
        if (name == "DC Tims Line") {
            std::cout << "|" << std::setw(7) << std::setfill(' ') << std::left << map.at(10)->getGuest();
        } else if (name == "Needles Hall") {
            std::cout << "|" << std::setw(7) << std::setfill(' ') << std::left << map.at(7)->getGuest();
        } else if (name == "MKV" || name == "SLC") {
            std::cout << "|       ";
        } else if (name == "Tuition") {
            std::cout << "|       ";
        } else if (name == "Collect OSAP") {
            std::cout << "|" << std::setw(7) << std::setfill(' ') << std::left << map.at(0)->getGuest();
        } else {
            std::cout << "|" << std::setw(7) << std::setfill(' ') << std::left << map.at(i)->getName();
        }
    }
    std::cout << "|" << std::endl;
    
    for (int i = 10; i >= 0; i -= 1) {
        std::string name = map.at(i)->getName();
        if (name == "HH" || name == "PAS" || name == "ECH" ||
            name == "ML" || name == "AL") {
            std::cout << "|" << std::setw(7) << std::setfill(' ') << std::left << map.at(i)->getGuest();
        } else {
            std::cout << "|       ";
        }
    }
    std::cout << "|" << std::endl;
    
    for (int i = 10; i >= 0; i -= 1) {
        std::cout << "|_______";
    }
    std::cout << "|" << std::endl;
}


// void gridSave(std::ostream &saveFile) will save all the information
//   in the whole grid.
void Grid::gridSave(std::ostream &saveFile) {
    for (int i = 0; i < (int)map.size(); i += 1) {
        if (map.at(i)->getType() != "EVENT") {
            if (map.at(i)->getOwner()) {
                propertyPtr p = map.at(i);
                saveFile << p->getName() << " " << p->getOwner()->getName() << " ";
                saveFile << p->getImproveLevel() << std::endl;
            }
        }
    }
}


// propertyPtr Grid::at(const int &position) will return the pointer at the
//   position, it will return nullptr if this is not a valid
//   position.
propertyPtr Grid::at(const int &position) {
    if (0 <= position && position < (int)map.size()) {
        return map.at(position);
    }
    return nullptr;
}


// propertyPtr Grid::find(std::string &name) will return the pointer of
//   the first property with the matched name in the map. If there is
//   no such property, then return nullptr.
propertyPtr Grid::find(std::string &name) {
    for (int i = 0; i < (int)map.size(); i += 1) {
        if (map.at(i)->getName() == name) {
            return map.at(i);
        }
    }
    return nullptr;
}


// void Grid::setSeed(const int _seed) will set a new seed to the grid
void Grid::setSeed(const int _seed) {
    seed = _seed;
    seedPermit = true;
}


// const int Grid::getLen(void) will return the len of the map.
const int Grid::getLen(void) { return (int)map.size(); }


// const int Grid::findPos(const std::string name) will return the position
//   of the given property
const int Grid::findPos(const std::string name) {
    for (int i = 0; i < (int)map.size(); i += 1) {
        if (map.at(i)->getName() == name) {
            return i;
        }
    }
    return 0;

}



// Destructor of Grid
Grid::~Grid() { std::cout << "The grid is destroyed." << std::endl; }
