
#include <stdio.h>
#include <SDL.h>


#ifndef __EventHandler__
#define __EventHandler__

class EventHandler {
public:
    EventHandler(SDL_DisplayMode& current);

    ~EventHandler();

    void handleEvents(int& offsetX, int& offsetY);

private:
    SDL_Event event;

    SDL_DisplayMode current;

    bool ctTrigger = false;

    int ctX = 0;

    int ctY = 0;

    int motionX;

    int motionY;

    void quit(SDL_Event& event);


    void mouseMotion(SDL_Event& event);


    void mouseDown(SDL_Event& event);


    void mouseUp(SDL_Event& event);


    void fingerMotion(SDL_Event& event, int& offsetX, int& offsetY);


    void fingerDown(SDL_Event& event);


    void fingerUp(SDL_Event& event);
};

#endif