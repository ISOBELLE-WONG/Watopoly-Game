#include "gotims.h"


// Constructor of GoTims
GoTims::GoTims(): Unownable("Go to Tims", false) { }


// const std::string GoTims::getMovement(playerPtr p) will return the instruction
//   that the position or the steps that the player should move.
const std::string GoTims::getMovement(Player *p) noexcept {
    return "DC Tims Line";
}
