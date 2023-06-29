# pragma once
#include <SDL2/SDL.h>

#define BAT_WIDTH 32
#define BAT_HEIGHT 120

class Bat {
    public:
        struct {
            int x;
            int y;
        } position;
        
        struct{
            int width = BAT_WIDTH;
            int height = BAT_HEIGHT;
        } dimensions;

        SDL_Rect rect;

        Bat();
        Bat(int x, int y);

        int left();
        int right();
        int top();
        int bottom();
        float centreX();
        float centreY();

        void updatePosition(int newY);
        void setVerticalPosition(int y);
        int getVerticalPosition();
        int getWidth();
        int getHeight();
};

