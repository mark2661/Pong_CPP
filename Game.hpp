#pragma one

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <stdio.h>
#include <cstdlib>
#include <cmath>
#include <cassert>
#include "utils.hpp"
#include "Player.hpp"
#include "Ball.hpp"
#include "LTexture.hpp"

class Game
{
    private:
        int screenWidth;
        int screenHeight;
        
    public:
        Player player1;
        Player player2;
        Ball ball;
        LTexture player1Score;
        LTexture player2Score;
        

        Game();
        Game(int screenWidth, int screenHeight);
        void processInputs();
        void batBoundaryCollisionCheck();
        void ballBoundaryCollisionCheck();
        void moveBall();
        void resetBall();
        void renderFrame(SDL_Renderer* renderer, TTF_Font* font);
        void run();
};

