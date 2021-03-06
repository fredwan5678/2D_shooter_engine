#ifndef SCREEN_HANDLER_H
#define SCREEN_HANDLER_H

#include <string>
#include <unordered_map>
#include <vector>

enum priority {
    BACKGROUND = 0,
    BACK = 1,
    MID = 2,
    FRONT = 3,
    FOREGROUND = 4
};

struct FutureState
{
    int x;
    int y;
    bool flip;
    double angle;
    int centerX;
    int centerY;
    int clipX;
    int clipY;
    int clipWidth;
    int clipHeight;
};

class ScreenHandler
{
private:
    std::unordered_map<std::string, FutureState> futures;
protected:
    void setFutureState(std::string tID, int x, int y, bool flip, double angle, int centerX, int centerY, int clipX, int clipY, int clipWidth, int clipHeight);
    
    void setFutureState(std::string tID, FutureState state);
    
    void removeFutureState(std::string tID);
    
    FutureState getFutureState(std::string tID);

    virtual bool openWindow(std::string header, int x, int y, int width, int height);
public:
    ScreenHandler();
    ~ScreenHandler();

    virtual void update();

    virtual std::string createSprite(std::string path, priority prio, int x, int y, int width, int height, bool flip = false, double angle = 0.0, int centerX = 0, int centerY = 0);

    virtual std::string createSprite(std::string path, priority prio, int x, int y, int width, int height, int clipX, int clipY, int clipWidth, int clipHeight, bool flip = false, double angle = 0.0, int centerX = 0, int centerY = 0);

    virtual void clipSprite(std::string tID, int clipX, int clipY, int clipWidth, int clipHeight);

    virtual void moveSprite(std::string tID, int x, int y, bool flip = false, double angle = 0.0, int centerX = 0, int centerY = 0);

    virtual void setRenderPriority(std::string tID, priority prio);

    virtual std::unordered_set<std::string> getKeysPressed();

    virtual std::pair<int, int> getMousePos();
};

#endif