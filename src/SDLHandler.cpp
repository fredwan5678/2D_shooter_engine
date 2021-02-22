#include "SDLhandler.h"

SDLHandler::SDLHandler(std::string header, int windowX, int windowY, int windowWidth, int windowHeight) {
    if( SDL_Init( SDL_INIT_VIDEO ) < 0 )
	{
        std::cout << "SDL could not init" << SDL_GetError() << std::endl;
        return;
	}

    // Do I need this??
    if( !SDL_SetHint( SDL_HINT_RENDER_SCALE_QUALITY, "1" ) )
    {
        std::cout << "Linear render scale not set!" << std::endl;
    }

    openWindow(header, windowX, windowY, windowWidth, windowHeight);

    renderer = SDL_CreateRenderer( window, -1, SDL_RENDERER_ACCELERATED);
    if( renderer == NULL )
    {
        std::cout << "Renderer not created!!!" << SDL_GetError() << std::endl;
        return;
    }

    SDL_SetRenderDrawColor( renderer, 0xFF, 0xFF, 0xFF, 0xFF );

    int imgFlags = IMG_INIT_PNG;
    if( !( IMG_Init( imgFlags ) & imgFlags ) )
    {
        std::cout << "SDL_image could not initialize!" << IMG_GetError() << std::endl;
        return;
    }
}

SDLHandler::~SDLHandler() {
    for (std::unordered_map<std::string, SDLTexture>::iterator it = allTextures.begin(); it != allTextures.end(); ++it) {
        (*it).second.free();
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    IMG_Quit();
	SDL_Quit();

    delete &background;
    delete &back;
    delete &mid;
    delete &front;
    delete &foreground;
}

void SDLHandler::renderNow(SDLTexture* tex, std::string tID) {
    FutureState future = getFutureState(tID);
    SDL_Rect clipQuad = {future.clipX, future.clipY, future.clipWidth, future.clipHeight};
    SDL_Point centerPoint = {future.centerX, future.centerY};
    SDL_RendererFlip flip = SDL_FLIP_NONE;
    if (future.flip) {
        flip = SDL_FLIP_HORIZONTAL;
    }
    tex->render(renderer, future.x, future.y, &clipQuad, future.angle, &centerPoint, flip);
}

void SDLHandler::update() {
    bool quit;
    while( SDL_PollEvent( &e ) != 0 )
    {
        //User requests quit
        if( e.type == SDL_QUIT )
        {
            quit = true;
        }
    }

    SDL_GetMouseState(&mousePosX, &mousePosX);

    const Uint8* keystate = SDL_GetKeyboardState(NULL);
    keys.clear();
    // temp, fix this mess
    if (SDL_BUTTON(SDL_BUTTON_LEFT)) {
        keys.insert("LMB");
    }
    if (SDL_BUTTON(SDL_BUTTON_RIGHT)) {
        keys.insert("RMB");
    }
    if (keystate[SDL_SCANCODE_W]) {
        keys.insert("W");
    }
    if (keystate[SDL_SCANCODE_A]) {
        keys.insert("A");
    }
    if (keystate[SDL_SCANCODE_S]) {
        keys.insert("S");
    }
    if (keystate[SDL_SCANCODE_D]) {
        keys.insert("D");
    }
    if (keystate[SDL_SCANCODE_E]) {
        keys.insert("E");
    }
    if (keystate[SDL_SCANCODE_Q]) {
        keys.insert("Q");
    }
    if (keystate[SDL_SCANCODE_LSHIFT]) {
        keys.insert("LShift");
    }


    for (std::unordered_map<std::string, SDLTexture*>::iterator it = background.begin(); it != background.end(); ++it) {
        renderNow((*it).second, (*it).first);
    }
    for (std::unordered_map<std::string, SDLTexture*>::iterator it = back.begin(); it != back.end(); ++it) {
        renderNow((*it).second, (*it).first);
    }
    for (std::unordered_map<std::string, SDLTexture*>::iterator it = mid.begin(); it != mid.end(); ++it) {
        renderNow((*it).second, (*it).first);
    }
    for (std::unordered_map<std::string, SDLTexture*>::iterator it = front.begin(); it != front.end(); ++it) {
        renderNow((*it).second, (*it).first);
    }
    for (std::unordered_map<std::string, SDLTexture*>::iterator it = foreground.begin(); it != foreground.end(); ++it) {
        renderNow((*it).second, (*it).first);
    }
}

bool SDLHandler::openWindow(std::string header, int x, int y, int width, int height) {
    window = SDL_CreateWindow( header.c_str(), x, y, width, height, SDL_WINDOW_SHOWN );
    if( window == NULL )
    {
        // throw exception maybe?
        std::cout << "Window could not be created! " << SDL_GetError() << std::endl;
    }
}

std::string SDLHandler::createSprite(std::string path, priority prio, int x, int y, int width, int height, bool flip = false, double angle = 0.0, int centerX = 0, int centerY = 0) {
    std::string id;
    SDLTexture* tex;
    switch (prio)
    {
    case priority::BACKGROUND:
        id = "BG"+std::to_string(background.size());
        tex = new SDLTexture(id, renderer, path, width, height);
        background[id] = tex;
        break;
    case priority::BACK:
        id = "B"+std::to_string(back.size());
        tex = new SDLTexture(id, renderer, path, width, height);
        back[id] = tex;
        break;
    case priority::MID:
        id = "M"+std::to_string(mid.size());
        tex = new SDLTexture(id, renderer, path, width, height);
        mid[id] = tex;
        break;
    case priority::FRONT:
        id = "F"+std::to_string(front.size());
        tex = new SDLTexture(id, renderer, path, width, height);
        front[id] = tex;
        break;
    case priority::FOREGROUND:
        id = "FG"+std::to_string(foreground.size());
        tex = new SDLTexture(id, renderer, path, width, height);
        foreground[id] = tex;
        break;
    default:
        std::cout << "Undefined priority. Sprite not created..." << std::endl;
        return "";
    }

    allTextures[id] = *tex;
    priorities[id] = prio;
    
    setFutureState(id, x, y, flip, angle, centerX, centerY, 0, 0, width, height);
    return id;
}

std::string SDLHandler::createSprite(std::string path, priority prio, int x, int y, int width, int height, int clipX, int clipY, int clipWidth, int clipHeight, bool flip = false, double angle = 0.0, int centerX = 0, int centerY = 0) {
    std::string id = createSprite(path, prio, x, y, width, height, flip, angle, centerX, centerY);
    
    setFutureState(id, x, y, flip, angle, centerX, centerY, clipX, clipY, clipWidth, clipHeight);

    return id;
}

void SDLHandler::clipSprite(std::string tID, int clipX, int clipY, int clipWidth, int clipHeight) {
    FutureState state = getFutureState(tID);
    state.clipX = clipX;
    state.clipY = clipY;
    state.clipWidth = clipWidth;
    state.clipHeight = clipHeight;
    setFutureState(tID, state);
}

void SDLHandler::moveSprite(std::string tID, int x, int y, bool flip = false, double angle = 0.0, int centerX = 0, int centerY = 0) {
    FutureState state = getFutureState(tID);
    state.x = x;
    state.y = y;
    state.flip = flip;
    state.angle = angle;
    state.centerX = centerX;
    state.centerY = centerY;
    setFutureState(tID, state);
}

void SDLHandler::setRenderPriority(std::string tID, priority prio) {
    priority prevPri = priorities[tID];
    SDLTexture* tex = &allTextures[tID];

    switch (prio)
    {
    case priority::BACKGROUND:
        background[tID] = tex;
        break;
    case priority::BACK:
        back[tID] = tex;
        break;
    case priority::MID:
        mid[tID] = tex;
        break;
    case priority::FRONT:
        front[tID] = tex;
        break;
    case priority::FOREGROUND:
        foreground[tID] = tex;
        break;
    default:
        std::cout << "Invalid priority" << std::endl;
        return;
    }

    switch (prevPri)
    {
    case priority::BACKGROUND:
        background.erase(tID);
        break;
    case priority::BACK:
        back.erase(tID);
        break;
    case priority::MID:
        mid.erase(tID);
        break;
    case priority::FRONT:
        front.erase(tID);
        break;
    case priority::FOREGROUND:
        foreground.erase(tID);
        break;
    default:
        break;
    }

    priorities[tID] = prio;
}

std::unordered_set<std::string> SDLHandler::getKeysPressed() {
    return keys;
}

std::pair<int, int> SDLHandler::getMousePos() {
    return std::make_pair(mousePosX, mousePosY);
}