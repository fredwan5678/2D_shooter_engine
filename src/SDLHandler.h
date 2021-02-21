#ifndef SDL_HANDLER_H
#define SDL_HANDLER_H

#include <vector>
#include "screenHandler.h"
#include "SDLTexture.h"

class SDLHandler : public ScreenHandler
{
private:
    SDL_Renderer* renderer;
    
public:
    SDLHandler(/* args */);
    ~SDLHandler();
};

#endif