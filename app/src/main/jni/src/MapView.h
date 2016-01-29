#include <string>
#include <SDL.h>
#include <SDL_main.h>
#include <SDL_image.h>
#include <stdio.h>
//#include <fstream.h>
#include "LTexture.h"
#include <EventHandler.h>
#include "TTile.h"
#include <vector>
#include <map>

#include <string.h>
#include <jni.h>
#include <android/log.h>


#ifndef __MapView__
#define __MapView__

class MapView {
public:
    MapView();

    ~MapView();

    bool init();

    bool loadMedia();

    void close();

    bool checkCollision(SDL_Rect a, SDL_Rect b);

    bool setTiles();

    int mod(int number, int modulus);

    SDL_Point *pixelXYToTileXY(int pixelX, int pixelY, SDL_Point *reuse);

    void countT(SDL_Rect camera);

    int correctX(int x);

    int correctY(int y);

    void correctOffset();


    void wmain(SDL_Renderer *ren, SDL_DisplayMode current);

    SDL_Window *gWindow = NULL;

    SDL_Renderer *gRenderer = NULL;



    std::vector<TTile *> *mylist;
    std::vector<TTile *> *unusedTiles;
    std::map<std::string, LTexture *> *textureCache;

    std::map<std::string, TTile *> tiles;

    int offsetX = 0;
    int offsetY = 0;

    int velocityX = 0;
    int velocityY = 0;

    SDL_Point upperLeft;
    SDL_Point lowerRight;

private:

};

#endif