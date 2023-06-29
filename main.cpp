#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include "Game.hpp"

#ifndef SCREEN_WIDTH
#define SCREEN_WIDTH 640
#endif

#ifndef SCREEN_HEIGHT
#define SCREEN_HEIGHT 480
#endif

#ifndef PAD
#define PAD 50
#endif


bool init();
void close();

// Rendering Window 
SDL_Window* gWindow = nullptr;

// Renderer
SDL_Renderer* gRenderer = nullptr;

// global font
TTF_Font* gFont = nullptr;

// texture
LTexture gTextTexture;

bool init()
{
    // Inititalisation flag
    bool success = true;

    if (SDL_Init(SDL_INIT_VIDEO) > 0)
    {
        printf("SDL could not initialise! SDL Error!: %s\n", SDL_GetError());
        success = false;
    }
    else
    {
        // set texture filtering to linear
        if (!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1"))
        {
            printf("Warning: Linear texture filtering not enabled!");
            success = false;
        }
        // create window
        gWindow = SDL_CreateWindow("PONG", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
                                   SCREEN_WIDTH, SCREEN_HEIGHT,SDL_WINDOW_SHOWN);

        if (gWindow == nullptr)
        {
            printf("Window could not be created! SDL ERROR: %s\n", SDL_GetError());
            success = false;
        }

        else
        {
            // create renderer for window
            gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
            if (gRenderer == nullptr)
            {
                printf("Renderer could not be created! SDL ERROR: %s\n", SDL_GetError());
                success = false;
            }
            else
            {
                // initiaslise renderer coulour
                SDL_SetRenderDrawColor(gRenderer, 0, 0, 0, 0xFF);

                if (TTF_Init() == -1)
                {
                    printf("SDL_ttf could not initialise! SDL_ttf Error: %s\n", TTF_GetError());
                    success = false;
                }

            }
        }
    }
    return success;
}

void close()
{
    // destroy renderer
    SDL_DestroyRenderer(gRenderer); 
    gRenderer = nullptr;

    // destroy window
    SDL_DestroyWindow(gWindow); 
    gWindow = nullptr;

    TTF_Quit();
    SDL_Quit();
}

int main()
{
    if (!init())
    {
        printf("Failed to initialise!\n");
    }
    else
    {

        // Game object
        Game game = Game(SCREEN_WIDTH, SCREEN_HEIGHT);

        bool quit = false;

        // SDL event handler
        SDL_Event event;

        // load font 
        gFont = TTF_OpenFont("data/pong_score_font.ttf", 80);
        if (gFont == NULL)
        {
            printf("Failed to load lazy font! SDL_ttf Error: %s\n", TTF_GetError());
            return 0;
        }

        while(!quit)
        {
            // process events queue
            while (SDL_PollEvent(&event) != 0)
            {
                if (event.type == SDL_QUIT) { quit = true; }
            } 

            game.run();

            // render frame
            game.renderFrame(gRenderer, gFont);

            SDL_RenderPresent(gRenderer);
        }

    }
    close();
    return 0;
}

