#include "Game.hpp"
#include <stdlib.h>
#include <string>

#ifndef PAD
#define PAD 50
#endif

Game::Game() {}

Game::Game(int screenWidth, int screenHeight)
{
    this->screenWidth = screenWidth;
    this->screenHeight = screenHeight;

    this->player1 = Player(0, screenHeight/2 - BAT_HEIGHT/2);
    this->player2 = Player(screenWidth - BAT_WIDTH, screenHeight/2 - BAT_HEIGHT/2);
    this->ball = Ball(screenWidth/2, screenHeight/2, 5, 5);

}

void Game::processInputs()
{
    const Uint8* currentKeyStates = SDL_GetKeyboardState(NULL);
    int batMoveValue = 10;

    if (currentKeyStates[SDL_SCANCODE_W])
    {
       this->player1.bat.updatePosition(-batMoveValue); 
    }

    if (currentKeyStates[SDL_SCANCODE_S])
    {
        this->player1.bat.updatePosition(batMoveValue);
    }

    if (currentKeyStates[SDL_SCANCODE_J])
    {
        this->player2.bat.updatePosition(-batMoveValue); 
    }

    if (currentKeyStates[SDL_SCANCODE_K])
    {
        this->player2.bat.updatePosition(batMoveValue);
    }
}

void Game::batBoundaryCollisionCheck()
{
    this->player1.bat.setVerticalPosition(clamp(this->player1.bat.getVerticalPosition(), 0, this->screenHeight - BAT_HEIGHT));
    this->player2.bat.setVerticalPosition(clamp(this->player2.bat.getVerticalPosition(), 0, this->screenHeight - BAT_HEIGHT));
}

void Game::ballBoundaryCollisionCheck()
{
    if (this->ball.bottom() > this->screenHeight or this->ball.top() < 0) {this->ball.velocity.y *= -1;}
    if (this->ball.right() > this->screenWidth or this->ball.left() < 0)
    {
        if (this->ball.left() < 0) {this->player2.incrementScore();}
        else {this->player1.incrementScore();}

        this->resetBall();
    } 
    this->ball.setVerticalPosition(clamp(this->ball.getVerticalPosition(), 0, this->screenHeight - this->ball.dimensions.height));
    this->ball.setHorizontalPosition(clamp(this->ball.getHorizontalPosition(), 0, this->screenWidth - this->ball.dimensions.width)); // need to change 

}

void Game::moveBall()
{
    this->ball.moveX();
    this->ball.moveY();

    // collision check player1 bat and ball
    if (SDL_HasIntersection(&player1.bat.rect, &ball.rect))
    {
        if (ball.velocity.x < 0)
        {
            ball.velocity.x *= -1.1f;
            ball.velocity.y = (ball.centreY() - player1.bat.centreY()) / (player1.bat.getHeight()/2) * (ball.velocity.x);
        }
    }

    // collision check player2 bat and ball
    if (SDL_HasIntersection(&player2.bat.rect, &ball.rect))
    {
        if (ball.velocity.x > 0)
        {
            ball.velocity.x *= -1.1f;
            ball.velocity.y = (ball.centreY() - player2.bat.centreY()) / (player2.bat.getHeight()/2) * (-ball.velocity.x);
        }

    }

    ballBoundaryCollisionCheck();
}

void Game::resetBall()
{
    int y = rand() % this->screenHeight;
   
    this->ball.setVerticalPosition(y);
    this->ball.setHorizontalPosition(this->screenWidth/2);
    this->ball.velocity.x = -5;
    this->ball.velocity.y = -5;
}

void Game::renderFrame(SDL_Renderer* renderer, TTF_Font* font)
{
    // clear screen
    SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, 0xFF); // black
    SDL_RenderClear(renderer);

    // render score text
    SDL_Color scoreTextColour = {0xFF, 0xFF, 0xFF}; //white
    std::string player1ScoreText = std::to_string(this->player1.getScore());
    std::string player2ScoreText = std::to_string(this->player2.getScore());
    player1Score.loadFromRenderedText(player1ScoreText, scoreTextColour, font, renderer);
    player2Score.loadFromRenderedText(player2ScoreText, scoreTextColour, font, renderer);

    player1Score.render((this->screenWidth / 2) - PAD - player1Score.getWidth(), 30, renderer, NULL);
    player2Score.render((this->screenWidth / 2) + PAD, 30, renderer, NULL);

    // render net
    SDL_SetRenderDrawColor(renderer, 0x80, 0x80, 0x80, 0xFF); // grey
    SDL_RenderDrawLine(renderer, this->screenWidth/2, 0, this->screenWidth/2, this->screenHeight);

    // render bats 
    SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF); // white
    // render player 1 bat
    SDL_RenderFillRect(renderer, &(this->player1.bat.rect));
    // render player 2 bat
    SDL_RenderFillRect(renderer, &(this->player2.bat.rect));

    // render ball
    SDL_RenderFillRect(renderer, &(this->ball.rect));

}

void Game::run()
{
    // process keyboard input
    this->processInputs();
    // check/handle if player bat has collided with the edge of the screen
    this->batBoundaryCollisionCheck();

    // move ball and check/handle collisions
    this->moveBall();
}
