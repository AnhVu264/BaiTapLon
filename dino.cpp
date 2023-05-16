#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <SDL_ttf.h>
#include <iostream>
#include <cstring>

#include "include/dino.h"
#include "include/ThreatsObject.h"
#include "include/game.h"

using namespace std;

static const int ground_level = 415;

Dino::Dino()
{
    DINO_pos_x = 130;
    DINO_pos_y = 415;
    DINO_vel_x = 0;
    DINO_vel_y = 0;
    //jumpDirection = 0;
    is_pause = false;

    mCollider.x = DINO_pos_x;
    mCollider.y = DINO_pos_y;
    mCollider.w = DINO_WIDTH;
    mCollider.h = DINO_HEIGHT;
}

bool Dino::onGround()
{
    //return (jumpDirection = 0);
}

void Dino::handleEvent(SDL_Event& e)
{
    /*if(e.type == SDL_KEYDOWN && e.key.repeat == 0 && e.key.keysym.sym == SDLK_SPACE)
    {
        DINO_vel_y += Jump;
        if (DINO_vel_y > Jump)
        {
            DINO_vel_y = Jump;
        }
        if (jumpDirection == 0)
        {
            jumpDirection = -1;
            DINO_vel_y = 5 ;
        }
    }

    if(e.type == SDL_KEYUP && e.key.repeat == 0 && e.key.keysym.sym == SDLK_SPACE)
    {
        DINO_vel_y -= Jump;
    }*/

    if(e.key.keysym.sym == SDLK_SPACE)
    {
        if (isBottom && !isJumping)
        {
            isJumping = true;
            isBottom = false;
        }
    }
}

void Dino::render()
{
    gDinoTexture.render( DINO_pos_x, DINO_pos_y);
}

void Dino::move(SDL_Rect& ThreatObject)
{
    DINO_pos_x += DINO_vel_x;
    mCollider.x = DINO_pos_x;

    if ((DINO_pos_x < 0) || (DINO_pos_x + DINO_WIDTH > SCREEN_WIDTH) || checkCollision(ThreatObject))
    {
        DINO_pos_x -= DINO_vel_x;
        mCollider.x = DINO_pos_x;
    }

    DINO_pos_y += DINO_vel_y;
    mCollider.y = DINO_pos_y;

    if ((DINO_pos_y < 0) || (DINO_pos_y + DINO_HEIGHT > SCREEN_HEIGHT) || checkCollision(ThreatObject))
    {
        DINO_pos_y -= DINO_vel_y;
        mCollider.y = DINO_pos_y;
    }
}

bool Dino::checkCollision(SDL_Rect ThreatObject)
{
    int DINO_left = mCollider.x;
    int DINO_right = mCollider.x + mCollider.w;
    int DINO_top = mCollider.y;
    int DINO_bottom = mCollider.y + mCollider.h;

    int Threat_left = ThreatObject.x;
    int Threat_right = ThreatObject.x + ThreatObject.w;
    int Threat_top = ThreatObject.y;
    int Threat_bottom = ThreatObject.y + ThreatObject.h;

    if (DINO_bottom <= Threat_top)
        return false;
    if (DINO_top >= Threat_bottom)
        return false;
    if (DINO_right <= Threat_left)
        return false;
    if (DINO_left >= Threat_right)
        return false;

    return true;
}

void Dino::jump()
{
    /*mCollider.y -= DINO_vel_y;
    mCollider.y += GRAVITY;

    if ((mCollider.y < 0) || (mCollider.y + DINO_HEIGHT > SCREEN_HEIGHT))
    {
        mCollider.y -= GRAVITY;
    }

    if (jumpDirection == 0)
        return;
    if (jumpDirection == -1 && DINO_pos_y >= (ground_level - DINO_JUMP))
    {
        if (!is_pause)
        {
            DINO_pos_y -= DINO_vel_y;
        }
        else
        {
            DINO_pos_y = DINO_pos_y;
        }
    }

    if (DINO_pos_y <= (ground_level - DINO_JUMP))
    {
        jumpDirection = 1;
    }
    if (jumpDirection == 1 && DINO_pos_y <= ground_level)
    {
        if (!is_pause)
        {
            DINO_pos_y += DINO_vel_y;
        }
        else
        {
            DINO_pos_y = DINO_pos_y;
        }
    }

    if (DINO_pos_y >= ground_level)
    {
        jumpDirection = 0;
    }*/

    if (isJumping)
    {
        DINO_pos_y -= GRAVITY;
    }
    else
    {
        DINO_pos_y += GRAVITY;
    }
    if (DINO_pos_y >= 415)
    {
        DINO_pos_y = 415;
        isBottom = true;
    }
    if (DINO_pos_y <= 315)
    {
        isJumping = false;
    }
}

/*void Dino::render_when_jump(LTexture &gDINO_Jumping, SDL_Renderer *&gRenderer)
{
    gDINO_Jumping.render(DINO_pos_x, DINO_pos_y, gRenderer);
}

void Dino::render_on_ground(LTexture &gDINO_Ground, SDL_Renderer *&gRenderer, SDL_Rect &DINO_Position,
                            SDL_Rect &DINO_rect, int &frame_width, int &frame)
{
    DINO_Position.x = 130;
    DINO_Position.y = 415;
    DINO_Position.w = frame_width;
    DINO_Position.h = gDINO_Ground.getHeight();

    if (!is_pause)
    {
        frame++;
        DINO_rect.x += frame_width;
        if (DINO_rect.x >= gDINO_Ground.getWidth())
        {
            DINO_rect.x = 0;
        }
    }
    else
    {
        DINO_rect.x = DINO_rect.x;
    }
    SDL_RenderCopy(gRenderer, gDINO_Ground.getTexture(), &DINO_rect, &DINO_Position);
}*/

void Dino::pause(SDL_Event e)
{
    if (e.type == SDL_KEYDOWN && e.key.repeat == 0 && e.key.keysym.sym == SDLK_p)
    {
        if (is_pause == false)
            is_pause = true;
        else
            is_pause = false;
    }
}

bool Dino::gameover(ThreatObject obstacle1, ThreatObject obstacle2)
{
//    DINO_pos_x = DINO_pos_x;
//    DINO_pos_y = DINO_pos_y;
    if (checkCollision(obstacle1.get_obstacle_1_dimension()) || checkCollision(obstacle2.get_obstacle_2_dimension()))
    {
        dead = true;
        return true;
    }

    return false;
}

void Dino::reset()
{
    DINO_vel_y = 0;
    is_pause = false;
    //jumpDirection = 0;
    DINO_pos_x = 130;
    DINO_pos_y = 415;
    mCollider.w = DINO_WIDTH;
    mCollider.h = DINO_HEIGHT;
}

bool Dino::lose()
{
    return dead;
}
