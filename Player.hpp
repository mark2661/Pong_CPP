#pragma once
#include <SDL2/SDL.h>
#include "Bat.hpp"

class Player{
    private:
        Uint8 score = 0;

    public:
        Bat bat;

        Player();
        Player(int x, int y);
        
        Uint8 getScore();
        void incrementScore();
        void updatePlayerBatPosition(int y);
        void render(SDL_Renderer* renderer);
};
