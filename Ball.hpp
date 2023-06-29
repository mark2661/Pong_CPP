#pragma once
#include <SDL2/SDL.h>

#define BALL_WIDTH 15 
#define BALL_HEIGHT 15 

class Ball{
    public:
        struct{
            float x;
            float y;
        }position; 
        
        struct{
            float x;
            float y;
            int speed;
        }velocity;

        struct{
            int width = BALL_WIDTH;
            int height = BALL_HEIGHT;
        }dimensions;


        SDL_Rect rect;

        Ball();
        Ball(float x, float y, float xVel, float yVel);

        int left();
        int right();
        int top();
        int bottom();
        float centreX();
        float centreY();
        void moveX();
        void moveY();
        void setVerticalPosition(float newX);
        void setHorizontalPosition(float newY);
        int getHorizontalPosition();
        int getVerticalPosition();
        int getWidth();
        int getHeight();
};
