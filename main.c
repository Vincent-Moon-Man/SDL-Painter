// SDL Libraries
#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>

// Standard Libraries
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>

void drawRect(SDL_Renderer *renderer, float x, float y, float width, float height) 
{
    SDL_FRect rect = {x, y, width, height};
    
    // Make rect and render rect
    SDL_RenderRect(renderer, &rect);

}

int main() {
    SDL_Window *pWindow;
    bool done = false;

    SDL_Init(SDL_INIT_VIDEO);

    pWindow = SDL_CreateWindow(
            "My window",
            512,
            512,
            0
    );

    if (pWindow == NULL) {
        SDL_LogError(SDL_LOG_CATEGORY_ERROR, "Could not create window: %s\n", SDL_GetError());
    }

    SDL_Renderer *pRenderer = SDL_CreateRenderer(pWindow, NULL);

    float mouseX, mouseY;


    bool fill = false;
    while (!done) {

        SDL_Event event;

        while (SDL_PollEvent(&event)) {
            SDL_GetMouseState(&mouseX, &mouseY);
            if (event.type == SDL_EVENT_QUIT) {
                done = true;
            }
            if (event.type == SDL_EVENT_MOUSE_BUTTON_DOWN){
                fill = true;
            }
            else if (event.type == SDL_EVENT_MOUSE_BUTTON_UP){
                fill = false;
            }
        }

        SDL_SetRenderDrawColor(pRenderer, 255,0,0,255);
        SDL_RenderClear(pRenderer);

        SDL_SetRenderDrawColor(pRenderer, 0,255,0,255);
        
        if (!fill) {
            drawRect(pRenderer, mouseX - 10, mouseY - 10, 20, 20);
        }

        // Set Background Color
        SDL_RenderPresent(pRenderer);
    }

    SDL_DestroyRenderer(pRenderer);
    SDL_DestroyWindow(pWindow);

    SDL_Quit();
    return 0;
}

