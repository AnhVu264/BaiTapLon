#ifndef DINO_H
#define DINO_H

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <SDL_ttf.h>
#include <iostream>
#include <cstring>

#include "game.h"
#include "ThreatsObject.h"

using namespace std;

class Dino
{
    public:
        Dino();

        static const int DINO_WIDTH = 40;
        static const int DINO_HEIGHT = 40;
        static const int DINO_JUMP = 100;
        const int GRAVITY = 20;
        const int Jump = 23;

        bool onGround();
        void move(SDL_Rect& ThreatObject);
        bool checkCollision(SDL_Rect ThreatObject);
        void jump();
        //void render_when_jump(LTexture &gDINO_Jumping, SDL_Renderer *&gRenderer);
       // void render_on_ground(LTexture &gDINO_Ground, SDL_Renderer *&gRenderer, SDL_Rect &DINO_Position,
                              //SDL_Rect &DINO_rect, int &frame_width, int &frame);

        void handleEvent(SDL_Event& e);
        void render();
        void pause(SDL_Event e);

        void reset();
        bool gameover(ThreatObject obstacle1, ThreatObject obstacle2);
        bool lose();

    private:
        bool dead = false;
        bool isJumping = false;
        bool isBottom = false;
        bool is_pause;
        int DINO_pos_x, DINO_pos_y;
        int DINO_vel_x, DINO_vel_y;
        //int jumpDirection;
        SDL_Rect mCollider;

};
extern LTexture gDinoTexture;
#endif //DINO_H
