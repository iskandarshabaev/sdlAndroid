/*This source code copyrighted by Lazy Foo' Productions (2004-2015)
and may not be redistributed without written permission.*/

//Using SDL, SDL_image, standard IO, strings, and file streams
#include <string.h>
#include <SDL.h>
#include <SDL_main.h>
#include <SDL_image.h>
#include <stdio.h>
//#include <fstream.h>
#include "LTexture.h"
#include "TTile.h"
#include <vector>
#include <map>

#include <string.h>
#include <jni.h>
#include <android/log.h>

#define APPNAME "SDL"


//Scene textures


//Starts up SDL and creates window
bool init();

//Loads media
bool loadMedia();

//Frees media and shuts down SDL
void close();

//Box collision detector
bool checkCollision(SDL_Rect a, SDL_Rect b);

//Sets tiles from tile map
bool setTiles();

int mod(int number, int modulus);

void handleEvent(SDL_Event & e);

SDL_Point *pixelXYToTileXY(int pixelX, int pixelY, SDL_Point *reuse);

void countT(SDL_Rect camera);

int correctX(int x);

int correctY(int y);

void correctOffset();


void handleMouseEvents(SDL_Event& event);

void handleTouchEvents(SDL_Event& event);

void wmain(SDL_Renderer *ren, SDL_Rect* camera);

//The window we'll be rendering to
SDL_Window *gWindow = NULL;

//The window renderer
SDL_Renderer *gRenderer = NULL;

using namespace std;

vector<TTile *> *mylist = new vector<TTile *>;
vector<TTile *> *unusedTiles = new vector<TTile *>;
map<string, LTexture *> *textureCache = new map<string, LTexture *>;

map<string, TTile *> tiles;

int offsetX = 0;
int offsetY = 0;

int velocityX = 0;
int velocityY = 0;

SDL_Point upperLeft;
SDL_Point lowerRight;



bool init() {
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
/*
    //Create window
    gWindow = SDL_CreateWindow("SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
                               SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
                               */
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

bool loadMedia() {
    //Loading success flag
    bool success = true;

    //Load dot texture
    /*
    LTexture *dotTexture = new LTexture();
    dot.setDotTexture(dotTexture);
    if (!dot.getDotTexture() ->loadFromFile(gRenderer, "D:/sdlTest/res/tiles/dot.bmp"))
    {
        printf("Failed to load dot texture!\n");
        success = false;
    }
    */

    /*
    for (int x = upperLeft.x; x <= lowerRight.x; x+=256 ) {
        for (int y = upperLeft.y; y <= lowerRight.y; y += 256) {
            SDL_Point *point = new SDL_Point();
            point -> x = x;
            point -> y = y;
            pixelXYToTileXY(x, y, point);

            TTile *tile = new TTile(x, y);
            LTexture *tileTexture = new LTexture();
            tileTexture ->loadFromFile(gRenderer,
                string("c:/graphics/openGL/shapes/sdlTest/res/tiles/") + "2" +
                to_string(point -> x) + to_string(point -> y) + ".png");
            tile->setTileTexture(tileTexture);
            mylist->push_back(tile);
        }
    }
    */

    /*
    for (int i = 0; i < (mylist -> size()); i++) {
        mylist -> at(i) -> getTileTexture() -> loadFromFile(gRenderer, "c:/graphics/openGL/shapes/sdlTest/res/0.png");
    }
    */
    return success;
}

void close() {
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

void wmain(SDL_Renderer *ren, SDL_DisplayMode current) {

    gRenderer = ren;

    upperLeft.x = 0;
    upperLeft.y = 0;

    lowerRight.x = 1024;
    lowerRight.y = 1024;


    //Start up SDL and create window
    /*
    if (!init()) {
        printf("Failed to initialize!\n");
    }
    else {
     */
        //Load media

        if (!loadMedia()) {
            __android_log_print(ANDROID_LOG_INFO, APPNAME, "Failed to load media %s\n", SDL_GetError());
            //printf("Failed to load media!\n");
        }
        else {
            //Main loop flag
            bool quit = false;

            //Event handler
            SDL_Event e;

            //The dot that will be moving around on the screen


            //Level camera
            SDL_Rect camera = {0, 0, current.w, current.h};

            //countT(camera);

            //While application is running
            while (!quit) {
                //Handle events on queue
                int delay = SDL_GetTicks();
                while (SDL_PollEvent(&e) != 0) {
                    //User requests quit
                    if (e.type == SDL_QUIT) {
                        quit = true;
                    }

                    //Handle input for the dot
                    handleEvent(e);
                    //offsetX += velocityX;
                    //offsetY += velocityY;


                    int current = SDL_GetTicks();

                    countT(camera);

                }

                //Move the dot
                //dot.move();
                //dot.setCamera(camera);

                countT(camera);


                //__android_log_print(ANDROID_LOG_ERROR, APPNAME, "SDL_SetRenderDrawColor: start %s\n", SDL_GetError());
                //Clear screen
                SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
                SDL_RenderClear(gRenderer);
                //__android_log_print(ANDROID_LOG_ERROR, APPNAME, "SDL_SetRenderDrawColor: end %s\n", SDL_GetError());
                //Render level
                for (int i = 0; i < mylist->size(); ++i) {
                    //mylist->at(i) -> move(velocityX, velocityY);
                    //__android_log_print(ANDROID_LOG_INFO, APPNAME, "mylist size:" + mylist->size() + "start %s\n");
                    mylist->at(i)->render(gRenderer, camera);
                    /*if (!mylist->at(i)->checkCollision(camera,
                        mylist->at(i)->getBox()))
                    {
                        //mylist->erase(mylist -> begin() + i);
                    }
                    */
                }

                //Render dot
                //dot.render(gRenderer, camera);

                //Update screen
                SDL_RenderPresent(gRenderer);
            }
        }

        //Free resources and close SDL
        //close();
}


void handleEvent(SDL_Event& e)
{
    //If a key was pressed
    if (e.type == SDL_KEYDOWN && e.key.repeat == 0)
    {
        //Adjust the velocity
        switch (e.key.keysym.sym)
        {
            case SDLK_UP: offsetY += 16; break;
            case SDLK_DOWN: offsetY -= 16; break;
            case SDLK_LEFT: offsetX += 16; break;
            case SDLK_RIGHT: offsetX -= 16; break;
        }
    }
        //If a key was released
    else if (e.type == SDL_KEYUP && e.key.repeat == 0)
    {
        //Adjust the velocity
        switch (e.key.keysym.sym)
        {
            case SDLK_UP: velocityY = 0; break;
            case SDLK_DOWN: velocityY = 0; break;
            case SDLK_LEFT: velocityX = 0; break;
            case SDLK_RIGHT: velocityX = 0; break;
        }
    }

    handleMouseEvents(e);
    handleTouchEvents(e);
}

bool mouseClickTriger = false;
int mouseClickX = 0;
int mouseClickY = 0;

double mouseScrollVelocity = 0.015;

void handleMouseEvents(SDL_Event& event)
{
    if (event.type == SDL_MOUSEMOTION)
    {
        if (mouseClickTriger) {
            offsetX -= (mouseClickX - event.motion.x)*mouseScrollVelocity;
            offsetY -= (mouseClickY - event.motion.y)*mouseScrollVelocity;
        }
    }

    if (event.type == SDL_MOUSEBUTTONDOWN)
    {
        if (event.button.button == SDL_BUTTON_LEFT)
        {
            //Get the mouse offsets
            mouseClickX = event.button.x;
            mouseClickY = event.button.y;
            mouseClickTriger = true;
        }
    }

    if (event.type == SDL_MOUSEBUTTONUP)
    {
        //If the left mouse button was pressed
        if (event.button.button == SDL_BUTTON_LEFT)
        {
            //Get the mouse offsets
            event.button.x;
            event.button.y;
            mouseClickTriger = false;
        }
    }
}


void handleTouchEvents(SDL_Event& event)
{
    if (event.type == SDL_FINGERMOTION)
    {
        if (mouseClickTriger) {
            offsetX -= (mouseClickX - event.motion.x)*mouseScrollVelocity;
            offsetY -= (mouseClickY - event.motion.y)*mouseScrollVelocity;
        }
    }

    if (event.type == SDL_FINGERDOWN)
    {
        if (event.button.button == SDL_BUTTON_LEFT)
        {
            //Get the mouse offsets
            mouseClickX = event.button.x;
            mouseClickY = event.button.y;
            mouseClickTriger = true;
        }
    }

    if (event.type == SDL_FINGERUP)
    {
        //If the left mouse button was pressed
        if (event.button.button == SDL_BUTTON_LEFT)
        {
            //Get the mouse offsets
            event.button.x;
            event.button.y;
            mouseClickTriger = false;
        }
    }
}

SDL_Point* pixelXYToTileXY(int pixelX, int pixelY, SDL_Point *reuse)
{
    reuse -> x = pixelX / 256;
    reuse -> y = pixelY / 256;
    return reuse;
}

void countT(SDL_Rect camera)
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

int correctX(int x) {
    int tileX = x;
    while (tileX * 256 >= lowerRight.x) {
        tileX = ((tileX * 256) - lowerRight.x) / 256;
    }
    return tileX;
}

int correctY(int y) {
    int tileY = y;
    while (tileY * 256 >= lowerRight.y) {
        tileY = ((tileY * 256) - lowerRight.y) / 256;
    }
    return tileY;
}

int mod(int number, int modulus) {
    if (number > 0)
        return number % modulus;

    while (number < 0)
        number += modulus;

    return number;
}


void correctOffset() {
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