#include <SDL.h>
#include <SDL_image.h>
#include <android/log.h>
#include <MapView.cpp>

#define APPNAME "SDL"

int SDL_main(int argc, char **argv)
{
    SDL_Window *win = 0;
    SDL_Renderer *ren = 0;
    SDL_Surface *bmp = 0;
    SDL_Texture* tex = 0;
    SDL_bool done = SDL_FALSE;

    const int SCREEN_WIDTH = 1280;
    const int SCREEN_HEIGHT = 1024;

    __android_log_print(ANDROID_LOG_VERBOSE, APPNAME, "SDL_main: %s\n", SDL_GetError());

    if (SDL_Init(SDL_INIT_EVERYTHING) == -1){
        __android_log_print(ANDROID_LOG_VERBOSE, APPNAME, "SDL_Init: %s\n", SDL_GetError());
        return 1;
    }
    win = SDL_CreateWindow("Hello World!", 0, 0, 640, 480, SDL_WINDOW_SHOWN | SDL_WINDOW_FULLSCREEN);
    if (win == 0){
        __android_log_print(ANDROID_LOG_ERROR, APPNAME, "SDL_CreateWindow: %s\n", SDL_GetError());
        return 1;
    }
    ren = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (ren == 0){
        __android_log_print(ANDROID_LOG_ERROR, APPNAME, "SDL_CreateRenderer: %s\n", SDL_GetError());
        return 1;
    }
    IMG_Init(IMG_INIT_PNG);
    bmp = IMG_Load("image2.png");
    if (!bmp) {
        __android_log_print(ANDROID_LOG_ERROR, APPNAME, "SDL_LoadBMP: %s\n", SDL_GetError());
        return 1;
    }
    tex = SDL_CreateTextureFromSurface(ren, bmp);
    SDL_FreeSurface(bmp);
    if (!tex) {
        __android_log_print(ANDROID_LOG_ERROR, APPNAME, "SDL_CreateTexture: %s\n", SDL_GetError());
        return 1;
    }


    SDL_Rect camera = {0, 0, SCREEN_WIDTH, SCREEN_HEIGHT};

    __android_log_print(ANDROID_LOG_INFO, APPNAME, "SDL_Success: %s\n", SDL_GetError());
    /*
    while (!done) {
        SDL_Event event;
        while(SDL_PollEvent(&event)) {
            if(event.type == SDL_QUIT || event.type == SDL_KEYDOWN || event.type == SDL_FINGERDOWN) {
                //done = SDL_TRUE;
                __android_log_print(ANDROID_LOG_INFO, APPNAME, "SDL_Event:  down %s\n", SDL_GetError());
            }
        }

        SDL_SetRenderDrawColor(ren, 0xA0, 0xA0, 0xA0, 0xFF);
        SDL_RenderCopy(ren, tex, NULL, NULL);
        SDL_RenderPresent(ren);
    }
*/

    wmain(ren);
    SDL_DestroyRenderer(ren);
    SDL_DestroyWindow(win);
    SDL_Quit();
    return 0;
}
