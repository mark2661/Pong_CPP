#include "Ball.hpp"

Ball::Ball() {}

Ball::Ball(float x, float y, float xVel, float yVel)
{
    this->position.x = x;
    this->position.y = y;
    this->velocity.x = xVel;
    this->velocity.y = yVel;
    this->velocity.speed = 5;
    this->rect = {x, y, this->dimensions.width, this->dimensions.height};
}


int Ball::left() {return this->position.x;}

int Ball::right() {return (this->position.x + this->dimensions.width);}

int Ball::top() {return this->position.y;}

int Ball::bottom() {return (this->position.y + this->dimensions.height);}

float Ball::centreX()
{
    return static_cast<float>(this->position.x) + (static_cast<float>(this->dimensions.width))/2.0f;
}

float Ball::centreY()
{
    return static_cast<float>(this->position.y) + (static_cast<float>(this->dimensions.height))/2.0f;
}

void Ball::moveX() 
{ 
    this->position.x += this->velocity.x; 
    this->rect.x = this->position.x; 
}

void Ball::moveY() 
{ 
    this->position.y += this->velocity.y;
    this->rect.y = this->position.y;
}

void Ball::setVerticalPosition(float newY)
{
    this->position.y = newY;
    this->rect.y = this->position.y;
}

void Ball::setHorizontalPosition(float newX)
{
    this->position.x = newX;
    this->rect.x = this->position.x;
}

int Ball::getVerticalPosition() { return this->position.y; }

int Ball::getHorizontalPosition() { return this->position.x; }

int Ball::getWidth() { return this->dimensions.width; }

int Ball::getHeight() { return this->dimensions.height; }
