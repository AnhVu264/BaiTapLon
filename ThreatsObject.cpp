#include "include/ThreatsObject.h"

using namespace std;

ThreatObject::ThreatObject()
{
    is_pause = false;

    posX_threat_1 = SCREEN_WIDTH;
    posY_threat_1 = 445;
    mwidth_1 = WIDTH_THREAT_1;
    mheight_1 = HEIGHT_THREAT_1;

    posX_threat_2 = SCREEN_WIDTH + 300;
    posY_threat_2 = 415;
    mwidth_2 = WIDTH_THREAT_2;
    mheight_2 = HEIGHT_THREAT_2;

    mCollider_1.x = posX_threat_1;
    mCollider_2.x = posX_threat_2;
    mCollider_1.y = posY_threat_1;
    mCollider_2.y = posY_threat_2;
    mCollider_1.w = WIDTH_THREAT_1;
    mCollider_1.h = HEIGHT_THREAT_1;
    mCollider_2.w = WIDTH_THREAT_2;
    mCollider_2.h = HEIGHT_THREAT_2;
}

void ThreatObject::render()
{
    gThreat1.render(posX_threat_1, posY_threat_1);
    gThreat2.render(posX_threat_2, posY_threat_2);
}
/*
void ThreatObject::render_threat_2()
{
    gThreat2.render_threat_2(posX_threat_2, posY_threat_2);
}*/

void ThreatObject::threat_move()
{
    if(!is_pause)
    {
        posX_threat_1 -= RUN_DISTANCE;
        posX_threat_2 -= RUN_DISTANCE;

        if(posX_threat_1 + mwidth_1 < 0)
            posX_threat_1 = SCREEN_WIDTH + 400;
        if(posX_threat_2 + mwidth_2 < 0)
            posX_threat_2 = SCREEN_WIDTH + 600;
    }
    else
    {
        posX_threat_1 = posX_threat_1;
        posX_threat_2 = posX_threat_2;
    }
}

void ThreatObject::pause(SDL_Event e)
{
    if(e.type == SDL_KEYDOWN && e.key.repeat == 0 && e.key.keysym.sym == SDLK_p)
    {
        if(is_pause == false) is_pause = true;
        else is_pause = false;
    }
}

SDL_Rect ThreatObject::get_obstacle_1_dimension()
{
    SDL_Rect res;
    res.x = posX_threat_1;
    res.y = posY_threat_1;
    res.w = mwidth_1;
    res.h = mheight_1;
    return res;
}

SDL_Rect ThreatObject::get_obstacle_2_dimension()
{
    SDL_Rect res;
    res.x = posX_threat_2;
    res.y = posY_threat_2;
    res.w = mwidth_2;
    res.h = mheight_2;
    return res;
}

void ThreatObject::gameOver()
{
    posX_threat_1 = posX_threat_1;
    posX_threat_2 = posX_threat_2;
}

void ThreatObject::reset()
{
    is_pause = false;

    posX_threat_1 = SCREEN_WIDTH;
    posY_threat_1 = SCREEN_HEIGHT;
    mwidth_1 = WIDTH_THREAT_1;
    mheight_1 = HEIGHT_THREAT_1;

    posX_threat_2 = SCREEN_WIDTH + 300;
    posY_threat_2 = SCREEN_HEIGHT;
    mwidth_2 = WIDTH_THREAT_2;
    mheight_2 = HEIGHT_THREAT_2;
}

