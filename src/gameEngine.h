#ifndef GAME_ENGINE_H
#define GAME_ENGINE_H

#include <vector>
#include "gameState.h"

class GameEngine
{
private:
    std::vector<GameState*> states;
    bool running;

public:
    GameEngine();
    ~GameEngine();

    void ChangeState(GameState* state);
    void PushState(GameState* state);
    void PopState();

    void HandleUserInput();
    void Update();
    void Render();
    bool IsRunning();
    void StopRunning();
};

#endif