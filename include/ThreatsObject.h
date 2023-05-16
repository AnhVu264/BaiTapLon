#ifndef THREATS_OBJECT_H
#define THREATS_OBJECT_H

#include "game.h"
#include "Function.h"
//#include "BaseObject.h"

#define WIDTH_THREAT_1 130
#define HEIGHT_THREAT_1 77

#define WIDTH_THREAT_2 145
#define HEIGHT_THREAT_2 77

#define RUN_DISTANCE 4


using namespace std;

class ThreatObject
{
    public:
        ThreatObject();

        void render();

        void threat_move();
        void pause(SDL_Event e);

        SDL_Rect get_obstacle_1_dimension();
        SDL_Rect get_obstacle_2_dimension();

        void reset();
        void gameOver();

    private:
        bool is_pause;
        int posX_threat_1, posY_threat_1;
        int mwidth_1, mheight_1;
        int posX_threat_2, posY_threat_2;
        int mwidth_2, mheight_2;
        SDL_Rect mCollider_1;
        SDL_Rect mCollider_2;
};

extern LTexture gThreat1;
extern LTexture gThreat2;
#endif // THREATS_OBJECT_H
