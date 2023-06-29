#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>
#include <string>
#include "Bat.h"
#include "Ball.h"
#include "Player.h"

#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 480
//#define BAT_WIDTH 32
//#define BAT_HEIGHT 120
//#define BALL_WIDTH 15
//#define BALL_HEIGHT 15
#define FPS 120

int clamp(int x, int low, int high);

typedef struct ball {
    int x = SCREEN_WIDTH/2;
    int y = SCREEN_HEIGHT/2;
    int xVel = 5;
    int yVel = 5;

    int left()
    {
        return x;
    }
    int right()
    {
        return x + BALL_WIDTH;
    }
    int top()
    {
        return y;
    }
    int bottom()
    {
        return y + BALL_HEIGHT;
    }

} BALL;

typedef struct bat {
    int x = 0;
    int y = SCREEN_HEIGHT/2 - BAT_HEIGHT/2;

    int left()
    {
        return x;
    }
    int right()
    {
        return x + BAT_WIDTH;
    }
    int top()
    {
        return y;
    }
    int bottom()
    {
        return y + BAT_HEIGHT;
    }            

    void boundaryCollisionCheck()
    {
        x = clamp(x, 0, SCREEN_WIDTH-BAT_WIDTH);
        y = clamp(y, 0, SCREEN_HEIGHT-BAT_HEIGHT);
    }

} BAT;

enum DIRECTION
{
    LEFT,
    RIGHT
};

bool init();
void close();
SDL_Texture* loadTexture(std::string const &);
void resetBall(BALL&, DIRECTION);
void handleCollisionHorizontal(BAT &, BALL &);
void handleCollisionVertical(BAT &, BALL &);

// Rendering window
SDL_Window* gWindow = nullptr;

// Texture
SDL_Texture* gTexture = nullptr;

// Renderer
SDL_Renderer* gRenderer = nullptr;


bool init()
{
    // Initialisation flag
    bool success = true;

    if (SDL_Init(SDL_INIT_VIDEO) > 0)
    {
        printf("SDL could not initialise! SDL Error!: &s\n", SDL_GetError());
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
                                   SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);

        if (gWindow == nullptr)
        {
            printf("Window could not be created! SDL ERROR: %s\n", SDL_GetError());
            success = false;
        }
        else
        {
            // create renderer for window
            gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
            //gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED);
            if (gRenderer == nullptr)
            {
                printf("Renderer could not be created! SDL Error: %s\n", SDL_GetError());
                success = false;
            }
            else
            {
                // initialsise renderer colour
                SDL_SetRenderDrawColor(gRenderer, 0, 0, 0, 0xFF);
            }
        }
    }
    return success;
}

void close()
{
    // destroy window
    SDL_DestroyRenderer(gRenderer);
    SDL_DestroyWindow(gWindow);
    gWindow = nullptr;
    gRenderer = nullptr;


   SDL_Quit();
}

int clamp(int x, int low, int high)
{
    if (x < low) {return low;}
    if (x > high) {return high;}
    return x;
}

void resetBall(BALL &ball, DIRECTION direction)
{
    ball.x = SCREEN_WIDTH / 2;
    //ball.y = SCREEN_HEIGHT / 2;
    ball.y = rand() % SCREEN_HEIGHT;

    if (direction == LEFT)
    {
        ball.xVel = -5;
    }
    else
    {
        //ball.xVel = 5;
        ball.xVel = -5; //test code remember to delete
    }

    ball.yVel *= -1;
}

void handleCollisionHorizontal(BAT &bat, BALL &ball)
{
    if ((ball.right() > bat.left() and  ball.right() < bat.right()) and (ball.top() > bat.top() and ball.bottom() < bat.bottom()))
    {
        if (ball.xVel > 0) // left side bat collision
        {
            ball.x = bat.left() - BALL_WIDTH;
        }
        else // right side bat collision
        {
            ball.x = bat.right();
        }
        ball.xVel *= -1;
    }
} 

void handleCollisionVertical(BAT &bat, BALL &ball)
{
    if ((ball.right() > bat.left() and ball.right() < bat.right()) and (ball.top() > bat.top() and ball.bottom() < bat.bottom()))
    {
        if (ball.yVel > 0) // top side bat collision
        {
            ball.y = bat.top() - BALL_HEIGHT;
        }
        else // bottom side bat collision
        {
            ball.y = bat.bottom();
        }
        ball.yVel *= -1;
    }
}

int main(int argc, char* argv[])
{
    if(!init())
    {
        printf("Failed to initialise!\n");
    }
    else
    {
        bool quit = false;

        // SDL event handler
        SDL_Event event;

        struct {
            Uint8 r = 0xFF;
            Uint8 g = 0xFF;
            Uint8 b = 0;
            Uint8 a = 0xFF;
            // yellow
        } myColour;

        struct {
            Uint8 r = 0;
            Uint8 g = 0;
            Uint8 b = 0xFF;
            Uint8 a = 0xFF;
            // blue
        } bat2Colour;


        BALL ball;
        BAT bat; 
        BAT bat2;
        bat2.x = SCREEN_WIDTH - BAT_WIDTH;


        while (!quit)
        {
            Uint32 currentTime = SDL_GetTicks();

            // process events queue
            while (SDL_PollEvent(&event) != 0)
            {
                if (event.type == SDL_QUIT)
                {
                    quit = true;
                }
            }

            int mouseX;
            int mouseY;
            SDL_GetMouseState(&mouseX, &mouseY);

            bat2.y = mouseY - BAT_HEIGHT/2;

            const Uint8* currentKeyStates = SDL_GetKeyboardState(NULL);
            
            if (currentKeyStates[SDL_SCANCODE_W])
            {
                   bat.y -= 10;
            }
            //else if (currentKeyStates[SDL_SCANCODE_D])
            //{
            //       bat.x += 10;
            //}
            //else if (currentKeyStates[SDL_SCANCODE_A])
            //{
            //       bat.x -= 10;
            //}
            else if (currentKeyStates[SDL_SCANCODE_S])
            {
                   bat.y += 10;
            }

            // boundary collision detection
            bat.boundaryCollisionCheck();
            bat2.boundaryCollisionCheck();

            // update ball position
            ball.x += ball.xVel;

            // bat ball collision
            // horizontal collision
            handleCollisionHorizontal(bat, ball);
            handleCollisionHorizontal(bat2, ball);
           
            ball.y += ball.yVel;

            // vertical collision
            handleCollisionVertical(bat, ball);
            handleCollisionVertical(bat2, ball);

            // ball boundary collision detection
            if (ball.bottom() > SCREEN_HEIGHT or ball.top() < 0) {ball.yVel *= -1;}
            if (ball.right() > SCREEN_WIDTH or ball.left() < 0)
            {
                DIRECTION dir = (ball.left() < 0) ? LEFT : RIGHT;

                resetBall(ball,dir);
            }

            // clear screen
            SDL_SetRenderDrawColor(gRenderer, 0, 0, 0, 0xFF); // black
            SDL_RenderClear(gRenderer);

            // render ball
            SDL_SetRenderDrawColor(gRenderer, 0xFF, 0, 0, 0xFF);  
            SDL_Rect ballRect = {ball.x, ball.y, BALL_WIDTH, BALL_HEIGHT};
            SDL_RenderFillRect(gRenderer, &ballRect);

            // render white filled rectangle
            SDL_Rect fillRect = {bat.x, bat.y, BAT_WIDTH, BAT_HEIGHT};
            SDL_SetRenderDrawColor(gRenderer, myColour.r, myColour.g, myColour.b, myColour.a);  
            SDL_RenderFillRect(gRenderer, &fillRect);

            // render second player bat
            SDL_Rect r2 = {bat2.x, bat2.y, BAT_WIDTH, BAT_HEIGHT};
            SDL_SetRenderDrawColor(gRenderer, bat2Colour.r, bat2Colour.g, bat2Colour.b, bat2Colour.a);  
            SDL_RenderFillRect(gRenderer, &r2);

            // update screen
            SDL_RenderPresent(gRenderer);
        }
    }
    
    // clean up
    close();
    return 0;
}
