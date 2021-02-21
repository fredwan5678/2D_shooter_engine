#include "screenHandler.h"

void ScreenHandler::setFutureState(std::string tID, int x, int y, bool flip, double angle, int centerX, int centerY, int clipX, int clipY, int clipWidth, int clipHeight) {
    FutureState newFuture = {x, y, flip, angle, centerX, centerY, clipX, clipY, clipWidth, clipHeight};
    futures[tID] = newFuture;
}

void ScreenHandler::setFutureState(std::string tID, FutureState state) {
    futures[tID] = state;
}

FutureState ScreenHandler::getFutureState(std::string tID) {
    return futures.at(tID);
}
void ScreenHandler::removeFutureState(std::string tID) {
    futures.erase(tID);
}