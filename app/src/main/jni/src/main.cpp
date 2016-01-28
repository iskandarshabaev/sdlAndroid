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


    __android_log_print(ANDROID_LOG_VERBOSE, APPNAME, "SDL_main: %s\n", SDL_GetError());

    if (SDL_Init(SDL_INIT_EVERYTHING) == -1){
        __android_log_print(ANDROID_LOG_VERBOSE, APPNAME, "SDL_Init: %s\n", SDL_GetError());
        return 1;
    }

    //win = SDL_CreateWindow("Hello World!", 0, 0, 1280, 1920, SDL_WINDOW_SHOWN | SDL_WINDOW_FULLSCREEN);
   // __android_log_print(ANDROID_LOG_VERBOSE, APPNAME, "start window creating %s\n");

    SDL_DisplayMode current;
    // Get current display mode of all displays.
    for(int i = 0; i < SDL_GetNumVideoDisplays(); ++i){

        int should_be_zero = SDL_GetCurrentDisplayMode(i, &current);

        if(should_be_zero != 0)
            // In case of error...
            SDL_Log("Could not get display mode for video display #%d: %s", i, SDL_GetError());

        else
            // On success, print the current display mode.
            SDL_Log("Display #%d: current display mode is %dx%dpx @ %dhz. \n", i, current.w, current.h, current.refresh_rate);

    }

    win = SDL_CreateWindow("Hello World!", 0, 0, current.w, current.h, SDL_WINDOW_SHOWN | SDL_WINDOW_FULLSCREEN);

   // __android_log_print(ANDROID_LOG_VERBOSE, APPNAME, "start window creating2 %s\n");



    if (win == 0){
        __android_log_print(ANDROID_LOG_ERROR, APPNAME, "SDL_CreateWindow: %s\n", SDL_GetError());
        return 1;
    }
   // __android_log_print(ANDROID_LOG_VERBOSE, APPNAME, "window created %s\n");
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




   // __android_log_print(ANDROID_LOG_INFO, APPNAME, "SDL_Success: %s\n", SDL_GetError());
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

    wmain(ren, current);
    SDL_DestroyRenderer(ren);
    SDL_DestroyWindow(win);
    SDL_Quit();
    return 0;
}
