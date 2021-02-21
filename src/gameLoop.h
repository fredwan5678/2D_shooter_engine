#ifndef GAME_LOOP_H
#define GAME_LOOP_H

#include <thread>

#include "logger.h" //remember to add lib to compiler include path
#include "gameEngine.h"


class GameLoop
{
private:
    std::thread renderThread;
    double interpolation = 0;

protected:
    *Logger logger;
    bool runningState;
    GameEngine controller;

    void Render();

    void ProcessGameLoop();

public:
    GameState(GameEngine engine);
    ~GameState();

    void Run();
    void Stop();
    bool IsRunning();
}

#endif