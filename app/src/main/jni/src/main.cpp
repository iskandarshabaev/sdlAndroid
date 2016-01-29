#include <SDL.h>
#include <SDL_image.h>
#include <android/log.h>
#include <MapView.h>

#define APPNAME "SDL"

int SDL_main(int argc, char **argv)
{
    SDL_Window *win = 0;

    SDL_bool done = SDL_FALSE;

    if (SDL_Init(SDL_INIT_EVERYTHING) == -1){
        __android_log_print(ANDROID_LOG_VERBOSE, APPNAME, "SDL_Init: %s\n", SDL_GetError());
        return 1;
    }

    SDL_DisplayMode current;
    for(int i = 0; i < SDL_GetNumVideoDisplays(); ++i){
        int should_be_zero = SDL_GetCurrentDisplayMode(i, &current);
        if(should_be_zero != 0)
            SDL_Log("Could not get display mode for video display #%d: %s", i, SDL_GetError());
        else
            SDL_Log("Display #%d: current display mode is %dx%dpx @ %dhz. \n", i, current.w, current.h, current.refresh_rate);
    }

    win = SDL_CreateWindow("Hello World!", 0, 0, current.w, current.h, SDL_WINDOW_SHOWN | SDL_WINDOW_FULLSCREEN);

    if (win == 0){
        __android_log_print(ANDROID_LOG_ERROR, APPNAME, "SDL_CreateWindow: %s\n", SDL_GetError());
        return 1;
    }


    MapView* mapView = new MapView(win);
    mapView->wmain(win);
    SDL_DestroyRenderer(ren);
    SDL_DestroyWindow(win);
    SDL_Quit();
    return 0;
}
