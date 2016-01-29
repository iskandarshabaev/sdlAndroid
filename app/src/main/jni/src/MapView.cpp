/*This source code copyrighted by Lazy Foo' Productions (2004-2015)
and may not be redistributed without written permission.*/

//Using SDL, SDL_image, standard IO, strings, and file streams
#include <MapView.h>
#include <string.h>
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


#define APPNAME "SDL"

using namespace std;


std::map<std::string, LTexture *> *textureCache = new std::map<std::string, LTexture *>;

std::vector<TTile *> *mylist = new std::vector<TTile *>;
std::vector<TTile *> *unusedTiles = new std::vector<TTile *>;

bool MapView::init() {
    //Initialization flag
    bool success = true;
    //LOGD("init start");


    if (SDL_Init(SDL_INIT_EVERYTHING) == -1){
        //LOGD("init start failed");
        //LOGD("SDL_Init: %s\n", SDL_GetError());
    }


    //LOGD("init start true");
    //Set texture filtering to linear
    if (!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1")) {
        printf("Warning: Linear texture filtering not enabled!");
    }
    if (gWindow == NULL) {
        printf("Window could not be created! SDL Error: %s\n", SDL_GetError());
        success = false;
    }
    else {
        //Create renderer for window
        gRenderer = SDL_CreateRenderer(gWindow, -1,
                                       SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
        if (gRenderer == NULL) {
            printf("Renderer could not be created! SDL Error: %s\n", SDL_GetError());
            success = false;
        }
        else {
            //Initialize renderer color
            SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);

            //Initialize PNG loading
            int imgFlags = IMG_INIT_PNG;
            if (!(IMG_Init(imgFlags) & imgFlags)) {
                printf("SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError());
                success = false;
            }
        }
    }


    upperLeft.x = 0;
    upperLeft.y = 0;

    lowerRight.x = 1024;
    lowerRight.y = 1024;

    return success;
}

bool MapView::loadMedia() {
    //Loading success flag
    bool success = true;
    return success;
}

void MapView::close() {
    //Free loaded images
    for (int i = 0; i < (mylist->size()); i++) {
//		mylist -> at(i)-> getTileTexture() -> free();
    }

    delete mylist;

    //Destroy window
    SDL_DestroyRenderer(gRenderer);
    SDL_DestroyWindow(gWindow);
    gWindow = NULL;
    gRenderer = NULL;

    //Quit SDL subsystems
    IMG_Quit();
    SDL_Quit();
}




void MapView::wmain(SDL_Renderer *ren, SDL_DisplayMode current) {

    gRenderer = ren;

    upperLeft.x = 0;
    upperLeft.y = 0;

    lowerRight.x = 1024;
    lowerRight.y = 1024;

    EventHandler* eventHandler = new EventHandler(current);
    if (!loadMedia()) {
        __android_log_print(ANDROID_LOG_INFO, APPNAME, "Failed to load media %s\n", SDL_GetError());
    }else {
        bool quit = false;
        SDL_Rect camera = {0, 0, current.w, current.h};
        while (!quit) {

            int delay = SDL_GetTicks();
            eventHandler->handleEvents(offsetX, offsetY);
            countT(camera);

            SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
            SDL_RenderClear(gRenderer);

            for (int i = 0; i < mylist->size(); ++i) {
                mylist->at(i)->render(gRenderer, camera);
            }

            SDL_RenderPresent(gRenderer);
        }
    }
}


SDL_Point* MapView::pixelXYToTileXY(int pixelX, int pixelY, SDL_Point *reuse)
{
    reuse -> x = pixelX / 256;
    reuse -> y = pixelY / 256;
    return reuse;
}

void MapView::countT(SDL_Rect camera)
{
    correctOffset();

    while(mylist ->size() > 50){
        delete mylist->at(0);
        mylist->erase(mylist->begin() +0);
    }

    int strXs = -offsetX;
    int strXe = -offsetX + camera.w;

    int strYs = -offsetY;
    int strYe = -offsetY + camera.h;

    int tileXs = (strXs ) / 256;
    int tileXe = (strXe  ) / 256;

    int tileYs = (strYs ) / 256;
    int tileYe = (strYe ) / 256;

    int mapTileUpperBound = 1 << 2;



    for (int x = tileXs -1 ; x < tileXe +1 ; x++) {
        for (int y = tileYs - 1; y < tileYe + 1; y++) {
            //x + offsetX;
            //pixelXYToTileXY(point->x, point->y, point);

            TTile *tile = NULL;
            if (unusedTiles->size() > 0) {
                tile = unusedTiles->at(0);
                unusedTiles->erase(unusedTiles -> begin() + 0);
            }
            else
            {
                tile = new TTile(0, 0);
            }

            int tileX = x;// mod(x, mapTileUpperBound);
            int tileY = y;// mod(y, mapTileUpperBound);


            if (x < upperLeft.x) {
                tileX = (lowerRight.x + (x * 256)) /256;
            }

            if (y < upperLeft.y) {
                tileY = (lowerRight.y + (y * 256)) / 256;
            }

            if (x >= lowerRight.x/256) {
                tileX = correctX(x);
                //tileX = ((x * 256) - lowerRight.x) / 256;
            }

            if (y >= lowerRight.y / 256) {
                tileY = correctY(y);
                //TileY = ((y * 256) - lowerRight.y) / 256;
            }

            string tileName = string("2") +
                              to_string(tileX) +
                              to_string(tileY);

            if (textureCache ->find(tileName) == (textureCache -> end())) {
                LTexture *tileTexture = new LTexture();

                tileTexture->loadFromFile(gRenderer,
                                          string("") + tileName + ".png");


                if (textureCache != NULL) {
                    tile->setTileTexture(tileTexture);
                    textureCache->insert(make_pair(tileName, tileTexture));
                    //mylist->push_back(tile);
                }
                else {

                }
            }
            else {
                tile->setTileTexture(textureCache->at(tileName));
                //mylist->push_back(tile);
            }
            // mylist->push_back(tile);

            int tx = x * 256 + offsetX;
            int ty = y * 256 + offsetY;
            //tile->setXY(tx, ty);
            if (tx >= camera.x + camera.w + 256) {
                tx = camera.x + (tx - lowerRight.x);
            }

            if (ty >= camera.y + camera.h + 256) {
                ty = camera.y + (ty - lowerRight.y);
            }

            if (tx < camera.x - 256) {
                tx = camera.x + (tx + lowerRight.x);
            }

            if (ty < camera.y - 256) {
                ty = camera.y + (ty + lowerRight.y);
            }
            tile->setXY(tx, ty);
            mylist->push_back(tile);
        }
    }
}

int MapView::correctX(int x) {
    int tileX = x;
    while (tileX * 256 >= lowerRight.x) {
        tileX = ((tileX * 256) - lowerRight.x) / 256;
    }
    return tileX;
}

int MapView::correctY(int y) {
    int tileY = y;
    while (tileY * 256 >= lowerRight.y) {
        tileY = ((tileY * 256) - lowerRight.y) / 256;
    }
    return tileY;
}

int MapView::mod(int number, int modulus) {
    if (number > 0)
        return number % modulus;

    while (number < 0)
        number += modulus;

    return number;
}


void MapView::correctOffset() {
    if (offsetX <= upperLeft.x - lowerRight.x) {
        offsetX = upperLeft.x + (lowerRight.x + offsetX);
    }

    if (offsetY <= upperLeft.y - lowerRight.y) {
        offsetY = upperLeft.y + lowerRight.y + offsetY;
    }

    if (offsetX > lowerRight.x) {
        offsetX = upperLeft.x + lowerRight.x - offsetX;
    }

    if (offsetY > lowerRight.y) {
        offsetY = upperLeft.y + lowerRight.y - offsetY;
    }
}