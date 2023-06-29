#include "Bat.hpp"

Bat::Bat() {}

Bat::Bat(int x, int y)
{
    this->position.x = x; 
    this->position.y = y; 
    this->rect = {x, y, this->dimensions.width, this->dimensions.height};
}

int Bat::left() { return this->position.x; }

int Bat::right() { return (this->position.x + this->dimensions.width); }

int Bat::top() { return this->position.y; }

int Bat::bottom() { return (this->position.y + this->dimensions.height); }

float Bat::centreX()
{
    return static_cast<float>(this->position.x) + ((static_cast<float>(this->dimensions.width)) / 2.0f);
}

float Bat::centreY()
{
    return static_cast<float>(this->position.y) + ((static_cast<float>(this->dimensions.height)) / 2.0f);
}

void Bat::updatePosition(int newY) 
{ 
    this->position.y += newY;
    this->rect.y = this->position.y;
}

void Bat::setVerticalPosition(int newY) 
{ 
    this->position.y = newY;
    this->rect.y = this->position.y;
}

int Bat::getVerticalPosition(){ return this->position.y; }

int Bat::getWidth() { return this->dimensions.width; }
int Bat::getHeight() { return this->dimensions.height; }
