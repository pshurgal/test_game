#include <iostream>
#include "SDL2/SDL.h"

using namespace std;

int main()
{
    SDL_Init(SDL_INIT_VIDEO);   // Initialize SDL2

    SDL_Window *window;        // Declare a pointer to an SDL_Window

    // Create an application window with the following settings:
    window = SDL_CreateWindow(
                "SDL2 Hello Window",         //    const char* title
                SDL_WINDOWPOS_UNDEFINED,  //    int x: initial x position
                SDL_WINDOWPOS_UNDEFINED,  //    int y: initial y position
                1024,                      //    int w: width, in pixels
                768,                      //    int h: height, in pixels
                SDL_WINDOW_SHOWN          //    Uint32 flags: window options, see docs
                );

    // Check that the window was successfully made
    if(window==nullptr){
        // In the event that the window could not be made...
        std::cout << "Could not create window: " << SDL_GetError() << '\n';
        SDL_Quit();
        return 1;
    }

    /* We must call SDL_CreateRenderer in order for draw calls to affect this window. */
    auto renderer = SDL_CreateRenderer(window, -1, 0);

    /* Select the color for drawing. It is set to red here. */
    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);

    /* Clear the entire screen to our selected color. */
    SDL_RenderClear(renderer);

    /* Up until now everything was drawn behind the scenes.
               This will show the new, red contents of the window. */
    SDL_RenderPresent(renderer);

    // The window is open: enter program loop (see SDL_PollEvent)
    SDL_Delay(3000);  // Wait for 3000 milliseconds, for example

    // Close and destroy the window
    SDL_DestroyWindow(window);

    // Clean up SDL2 and exit the program
    SDL_Quit();
    return 0;
}
