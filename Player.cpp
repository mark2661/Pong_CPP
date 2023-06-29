#include "Player.hpp"

Player::Player(){}

Player::Player(int x, int y)
{
    this->bat = Bat(x, y);
}

Uint8 Player::getScore(){return this->score;}

void Player::incrementScore(){this->score += 1;}

void Player::updatePlayerBatPosition(int y) { this->bat.updatePosition(y); }

void Player::render(SDL_Renderer* renderer)
{
   SDL_RenderFillRect(renderer, &(this->bat.rect));
}

