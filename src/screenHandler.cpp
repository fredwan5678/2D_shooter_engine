#include "screenHandler.h"

void ScreenHandler::createFutureState(std::string tID, int x, int y, bool flip, double angle, int centerX, int centerY, int clipX, int clipY, int clipWidth, int clipHeight) {
    FutureState newFuture = {x, y, flip, angle, centerX, centerY, clipX, clipY, clipWidth, clipHeight};
    futures->insert({tID, newFuture});
}

ScreenHandler::FutureState* ScreenHandler::getFutureState(std::string tID) {
    return &futures->at(tID);
}