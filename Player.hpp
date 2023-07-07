#pragma once
#include <SDL2/SDL.h>
#include "Bat.hpp"

class Player{

    public:
        Uint8 score = 0;
        Bat bat;

        Player();
        Player(int x, int y);
        
        Uint8 getScore();
        void incrementScore();
        void updatePlayerBatPosition(int y);
        void render(SDL_Renderer* renderer);
};
