#include "SDLTexture.h"

SDLTexture::SDLTexture(SDL_Renderer* renderer, std::string path) {
    loadFromPNG(renderer, path);
}

SDLTexture::~SDLTexture() {
    if(texture != NULL)
	{
		SDL_DestroyTexture(texture);
		texture = NULL;
		width = 0;
		height = 0;
	}
}

bool SDLTexture::loadFromPNG(SDL_Renderer* renderer, std::string path) {
	SDL_Surface* loadedSurface = IMG_Load(path.c_str());
	if(loadedSurface == NULL)
	{
		std::cout << "woops, Can't load image. Error says this: " << IMG_GetError() << std::endl;
	}
	else
	{
        texture = SDL_CreateTextureFromSurface(renderer, loadedSurface);
		if(texture == NULL)
		{
			printf("Unable to create texture from %s! SDL Error: %s\n", path.c_str(), SDL_GetError());
		}
		else
		{
			width = loadedSurface->w;
			height = loadedSurface->h;
		}

		SDL_FreeSurface(loadedSurface);
	}

	return texture != NULL;
}

void SDLTexture::setBlending(SDL_BlendMode blending) {
    SDL_SetTextureBlendMode(texture, blending);
}

void SDLTexture::setAlpha(Uint8 alpha) {
    SDL_SetTextureAlphaMod(texture, alpha);
}

void SDLTexture::render(SDL_Renderer* renderer, int x, int y, SDL_Rect* clip = NULL, double angle = 0.0, SDL_Point* center = NULL, SDL_RendererFlip flip = SDL_FLIP_NONE) {
    SDL_Rect renderQuad = {x, y, width, height};

    if(clip != NULL)
    {
        renderQuad.w = clip->w;
        renderQuad.h = clip->h;
    }

    SDL_RenderCopyEx(renderer, texture, clip, &renderQuad, angle, center, flip);
}

int SDLTexture::getWidth() {
    return width;
}

int SDLTexture::getHeight() {
    return height;
}