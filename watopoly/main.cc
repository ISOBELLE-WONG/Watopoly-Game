#include <string>
#include <fstream>
#include <iostream>
#include "controller.h"


int main(int argc, char *argv[]) {
    std::string fileName;
    bool loadPermit = true, testPermit = true, seedPermit = true;
    Controller controller{};
    try {
        for (int i = 1; i < argc; i += 1) {
            std::string command{argv[i]};
            if (command == "-testing") {
                if (!testPermit) { throw "Test Permit is already banned."; }
                if (!seedPermit) { throw "Test Permit is already banned."; }
                std::cout << "Test mode is now initialized!" << std::endl;
                controller.GameTest();
                testPermit = false;
            } else if (command == "-load") {
                if (!loadPermit) { throw "Loading File exists."; }
                std::cout << "Load mode is now initialized!" << std::endl;
		fileName = argv[++i];
		std::cout << "The game will load data from " << fileName << std::endl;
                loadPermit = false;
            } else if (command == "-seed") {
                if (!testPermit) { throw "Seed Permit is already banned."; }
                if (!seedPermit) { throw "Seed Permit is already banned."; }
                std::cout << "Seed mode is now initialized!" << std::endl;
                int seed = std::stoi(std::string{argv[++i]});
                controller.GameSeed(seed);
                seedPermit = false;
            } else {
                throw "Invalid argument exists.";
            }
        }
    } catch (const std::string &error) {
        std::cerr << error << std::endl;
        return 1;
    } catch(std::out_of_range &e) {
        std::cerr << e.what() << std::endl;
        return 1;
    } catch(std::invalid_argument &e) {
        std::cerr << e.what() << std::endl;
        return 1;
    }
    try {
        if (!loadPermit) {
            std::ifstream loadingFile{fileName};
            if (loadingFile.fail()) {
                std::cerr << "Loading file is not exist or not readable!" << std::endl;
                return 1;
            }
            controller.GameLoad(loadingFile);
        } else {
            controller.GameInit();
        }
    } catch(const std::string &e) {
        std::cerr << e << std::endl;
    }
    controller.GamePlay();
    controller.controllerClean();
    std::cout << "Watopoly Game is over!" << std::endl;
    std::cout << "Thank you for playing!" << std::endl;
}

