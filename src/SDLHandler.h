#ifndef SDL_HANDLER_H
#define SDL_HANDLER_H

#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <iostream>
#include "screenHandler.h"
#include "SDLTexture.h"

class SDLHandler : public ScreenHandler
{
private:
    SDL_Renderer* renderer;

    std::unordered_map<std::string, priority> priorities;
    std::unordered_map<std::string, SDLTexture> allTextures;

    std::unordered_map<std::string, SDLTexture*> background;
    std::unordered_map<std::string, SDLTexture*> back;
    std::unordered_map<std::string, SDLTexture*> mid;
    std::unordered_map<std::string, SDLTexture*> front;
    std::unordered_map<std::string, SDLTexture*> foreground;

    SDL_Event e;

    int mousePosX;
    int mousePosY;

    std::unordered_set<std::string> keys;

    SDL_Window* window;
    int windowX;
    int windowY;
    int windowWidth;
    int windowHeight;

    void renderNow(SDLTexture* tex, std::string tID);

protected:
    bool openWindow(std::string header, int x, int y, int width, int height);
public:
    SDLHandler(std::string header, int windowX, int windowY, int windowWidth, int windowHeight);
    ~SDLHandler();

    void update();

    bool openWindow(std::string header, int x, int y, int width, int height);

    std::string createSprite(std::string path, priority prio, int x, int y, int width, int height, bool flip = false, double angle = 0.0, int centerX = 0, int centerY = 0);

    std::string createSprite(std::string path, priority prio, int x, int y, int width, int height, int clipX, int clipY, int clipWidth, int clipHeight, bool flip = false, double angle = 0.0, int centerX = 0, int centerY = 0);

    void clipSprite(std::string tID, int clipX, int clipY, int clipWidth, int clipHeight);

    void moveSprite(std::string tID, int x, int y, bool flip = false, double angle = 0.0, int centerX = 0, int centerY = 0);

    void setRenderPriority(std::string tID, priority prio);

    std::unordered_set<std::string> getKeysPressed();

    std::pair<int, int> getMousePos();
};

#endif