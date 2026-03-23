// SDL Libraries
#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>

// Standard Libraries
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>

void drawRect(SDL_Renderer *renderer, bool filled, float x, float y, float width, float height) 
{
    SDL_FRect rect = {x, y, width, height};
    
    // Make rect and render rect
    if (filled) {
        SDL_RenderFillRect(renderer, &rect);
    } else {
        SDL_RenderRect(renderer, &rect);
    }
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

    int r, g, b;
    r = g = b = 255;
    int w, h;
    w = h = 20;

    bool draw = false;
    bool fill = false;

    while (!done) {

        SDL_Event event;

        while (SDL_PollEvent(&event)) {
            SDL_GetMouseState(&mouseX, &mouseY);

            if (event.type == SDL_EVENT_QUIT) {
                done = true;
            }

            if (event.type == SDL_EVENT_MOUSE_BUTTON_DOWN){
                draw = true;
                if (event.button.button == SDL_BUTTON_LEFT) {
                    fill = true;
                }
                else {
                    fill = false;
                }
            }
            else if (event.type == SDL_EVENT_MOUSE_BUTTON_UP){
                 draw = false;
            }

            if (event.type == SDL_EVENT_MOUSE_WHEEL) {
                if (event.wheel.y > 0) {
                    w += 10;
                    h += 10;    
                }

                if (event.wheel.y < 0) {
                    w -= 10;
                    h -= 10;    
                }
            }

            switch (event.key.key) {
            case SDLK_C:
                SDL_SetRenderDrawColor(pRenderer, r, g, b,255);
                SDL_RenderClear(pRenderer);
                break;

            case SDLK_1:
                g = b = 0;
                r = 255;
                break;
            
            case SDLK_2:
                r = b = 0;
                g = 255;
                break;
            
            case SDLK_3:
                r = g = 0;
                b = 255;
                break;

            case SDLK_4:
                r = g = b = 255;
                break;

            case SDLK_5:
                r = g = b = 0;
                break;
            }
        }

        SDL_SetRenderDrawColor(pRenderer, r, g, b,255);
        
        if (draw) {
            drawRect(pRenderer, fill, mouseX - w / 2, mouseY - h / 2, w, h);
        }

        // Set Background Color
        SDL_RenderPresent(pRenderer);
    }

    SDL_DestroyRenderer(pRenderer);
    SDL_DestroyWindow(pWindow);

    SDL_Quit();
    return 0;
}

