#ifndef SDL_TEXTURE_H
#define SDL_TEXTURE_H

#include <SDL.h>
#include <SDL_image.h>
#include <string>
#include <iostream>

class SDLTexture
{
public:
    SDLTexture(SDL_Renderer* renderer, std::string path);
    ~SDLTexture();

    bool loadFromPNG(SDL_Renderer* renderer, std::string path);

    void setBlending(SDL_BlendMode blending);

    void setAlpha(Uint8 alpha);
    
    void render(SDL_Renderer* renderer, int x, int y, SDL_Rect* clip = NULL, double angle = 0.0, SDL_Point* center = NULL, SDL_RendererFlip flip = SDL_FLIP_NONE);

    int getWidth();
    int getHeight();

private:
    SDL_Texture* texture;

    int width;
    int height;
};

#endif