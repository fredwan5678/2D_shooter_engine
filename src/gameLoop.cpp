#include "gameLoop.h"

GameLoop::GameLoop(GameEngine engine)
{
    #ifdef DEBUG
    //if debug, log stuff differently
    #endif
}

GameLoop::~GameLoop()
{
    delete Logger;
}

void GameLoop::Render()
{
    controller.Render();
}

void GameLoop::ProcessGameLoop()
{
    while (/* condition */)
    {
        /* code */
    }
    
}

void GameLoop::Run()
{

}

void GameLoop::Stop()
{

}

bool GameLoop::IsRunning()
{

}

int main( int argc, char* args[] )
{
    return 0;
}