//
// Created by i.shabaev on 29.01.2016.
//

#include "EventHandler.h"
#include <SDL.h>
#include <android/log.h>
#include <iostream>
#include <string>
#define APPNAME "SDL"

EventHandler::EventHandler(SDL_DisplayMode& current)
{
    this->current = current;
}


EventHandler::~EventHandler()
{

}


void EventHandler::handleEvents(int& offsetX, int& offsetY)
{
    while (SDL_PollEvent(&event) != 0) {
        switch(event.type)
        {
            case SDL_QUIT:
                quit(event);
                break;
            case SDL_MOUSEMOTION:
                mouseMotion(event);
                break;
            case SDL_MOUSEBUTTONDOWN:
                mouseDown(event);
                break;
            case SDL_MOUSEBUTTONUP:
                mouseUp(event);
            case SDL_FINGERMOTION:
                fingerMotion(event, offsetX, offsetY);
                break;
            case SDL_FINGERDOWN:
                fingerDown(event);
                break;
            case SDL_FINGERUP:
                fingerUp(event);
                break;
        }
    }
}


void EventHandler::quit(SDL_Event& event){

}


void EventHandler::mouseMotion(SDL_Event& event){

}


void EventHandler::mouseDown(SDL_Event& event){

}


void EventHandler::mouseUp(SDL_Event& event){

}


void EventHandler::fingerMotion(SDL_Event& event, int& offsetX, int& offsetY){
    if(ctTrigger) {
        motionX = (int) (event.tfinger.x * current.w);
        motionY = (int) (event.tfinger.y * current.h);
        offsetX -= (ctX - event.motion.x);
        offsetY -= (ctY - event.motion.y);
    }
}


void EventHandler::fingerDown(SDL_Event& event){
    ctX = (int)(event.tfinger.x * current.w);
    ctY = (int)(event.tfinger.y * current.h);
    motionX = ctX;
    motionY = ctY;
    ctTrigger = true;
}


void EventHandler::fingerUp(SDL_Event& event){
    ctTrigger = false;
}