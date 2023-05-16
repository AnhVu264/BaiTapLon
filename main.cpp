#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <SDL_ttf.h>
#include <iostream>
#include <string>

#include "include/game.h"
#include "include/dino.h"
#include "include/ThreatsObject.h"
#include "include/Function.h"
//#include "include/BaseObject.h"

using namespace std;

SDL_Window* gWindow = NULL;
SDL_Renderer* gRenderer = NULL;

Mix_Music *gMusic = NULL;

LTexture gDinoTexture;
LTexture gBGTexture;
LTexture gThreat1, gThreat2;
//LTexture gPause;

ThreatObject obstacle1, obstacle2;

SDL_Rect threat1;
SDL_Rect threat2;

bool is_game_over = false;
//bool is_pause = false;
/*TTF_Font *gFont = NULL;

LTexture gPromptTextTexture;

LTexture gInputTextTexture;*/

bool init();

bool loadMedia();

void close();

bool init()
{
    bool success = true;

    if( SDL_Init( SDL_INIT_VIDEO | SDL_INIT_AUDIO ) < 0 )
    {
        printf( "SDL could not initialize! SDL Error: %s\n", SDL_GetError() );
        success = false;
    }
    else
    {
        if( !SDL_SetHint( SDL_HINT_RENDER_SCALE_QUALITY, "1" ) )
        {
            printf( "Warning: Linear texture filtering not enabled!" );
        }

        gWindow = SDL_CreateWindow( "DINO RUNNING GAME", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN );
        if( gWindow == NULL )
        {
            printf( "Window could not be created! SDL Error: %s\n", SDL_GetError() );
            success = false;
        }
        else
        {
            gRenderer = SDL_CreateRenderer( gWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC );
            if( gRenderer == NULL )
            {
                printf( "Renderer could not be created! SDL Error: %s\n", SDL_GetError() );
                success = false;
            }
            else
            {
                SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );

                int imgFlags = IMG_INIT_PNG;
                if( !( IMG_Init( imgFlags ) & imgFlags ) )
                {
                    printf( "SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError() );
                    success = false;
                }

                //Initialize SDL_mixer
                if( Mix_OpenAudio( 44100, MIX_DEFAULT_FORMAT, 2, 2048 ) < 0 )
                {
                    printf( "SDL_mixer could not initialize! SDL_mixer Error: %s\n", Mix_GetError() );
                    success = false;
                }

                //Initialize SDL_ttf
                /*if( TTF_Init() == -1 )
                {
                	printf( "SDL_ttf could not initialize! SDL_ttf Error: %s\n", TTF_GetError() );
                	success = false;
                }*/
            }
        }
    }

    return success;
}

bool loadMedia()
{
    //Loading success flag
    bool success = true;

    //Open the font
    /*gFont = TTF_OpenFont( "lazy.ttf", 28 );
    if( gFont == NULL )
    {
    	printf( "Failed to load lazy font! SDL_ttf Error: %s\n", TTF_GetError() );
    	success = false;
    }
    else
    {
    	//Render the prompt
    	SDL_Color textColor = { 0, 0, 0, 0xFF };
    	if( !gPromptTextTexture.loadFromRenderedText( "Enter Text:", textColor ) )
    	{
    		printf( "Failed to render prompt text!\n" );
    		success = false;
    	}
    }*/

    if (!gDinoTexture.loadFromFile( "res/gfx/dinosaur2.png"))
    {
        printf( "Failed to load Dino texture!\n" );
        success = false;
    }

    if( !gBGTexture.loadFromFile( "res/gfx/background2.png" ) )
    {
        printf( "Failed to load background texture!\n" );
        success = false;
    }

    gMusic = Mix_LoadMUS( "res/gfx/game music 2.wav" );
    if (gMusic == NULL)
    {
        printf( "Failed to load beat music! SDL_mixer Error: %s\n", Mix_GetError() );
        success = false;
    }

    if( !gThreat1.loadFromFile( "res/gfx/rock1.png" ) )
    {
        printf( "Failed to load Threat!\n" );
        success = false;
    }

    if( !gThreat2.loadFromFile( "res/gfx/rock2.png" ) )
    {
        printf( "Failed to load Threat!\n" );
        success = false;
    }


    return success;
}

void close()
{
    //gPromptTextTexture.free();
    //gInputTextTexture.free();

    //TTF_CloseFont (gFont);
    //gFont = NULL;

    gDinoTexture.free();
    gBGTexture.free();
    gThreat1.free();
    gThreat2.free();

    Mix_FreeMusic (gMusic);
    gMusic = NULL;

    SDL_DestroyRenderer (gRenderer);
    SDL_DestroyWindow (gWindow);
    gWindow = NULL;
    gRenderer = NULL;

    //TTF_Quit();
    Mix_Quit();
    IMG_Quit();
    SDL_Quit();
}

int main( int argc, char* args[] )
{


    if( !init() )
    {
        printf( "Failed to initialize!\n" );
    }
    else
    {
        if( !loadMedia() )
        {
            printf( "Failed to load media!\n" );
        }
        else
        {
            bool quit = false;

            SDL_Event e;

            Dino dino;

            ThreatObject ThreatObject;

            int scrollingOffset = 0;

            /*SDL_Color textColor = { 0, 0, 0, 0xFF };

            string inputText = "Score:";
            gInputTextTexture.loadFromRenderedText( inputText.c_str(), textColor );

            SDL_StartTextInput();*/

            while( !quit )
            {
                //bool renderText = false;
                while( SDL_PollEvent( &e ) != 0 )
                {
                    if( e.type == SDL_QUIT )
                    {
                        quit = true;
                    }

                    dino.handleEvent(e);

                    if( e.type == SDL_KEYDOWN )
                    {
                        switch( e.key.keysym.sym )
                        {
                        case SDLK_9:
                            if( Mix_PlayingMusic() == 0 )
                            {
                                Mix_PlayMusic( gMusic, -1 );
                            }
                            else
                            {
                                if( Mix_PausedMusic() == 1 )
                                {
                                    Mix_ResumeMusic();
                                }
                                else
                                {
                                    Mix_PauseMusic();
                                }
                            }
                            break;

                        case SDLK_0:
                            Mix_HaltMusic();
                            break;
                        case SDLK_SPACE:
                            dino.jump();
                            break;
                            /*if (is_pause)
                            {
                                case SDLK_p:
                                dino.pause(e);
                                obstacle1.pause(e);
                                obstacle2.pause(e);
                                break;
                            }
                            case SDLK_BACKSPACE:
                                if (inputText.length() > 0)
                                {
                                    inputText.pop_back();
                                    renderText = true;
                                }
                                break;
                            case SDLK_c:
                                if (SDL_GetModState() & KMOD_CTRL)
                                {
                                    SDL_SetClipboardText (inputText.c_str());
                                }
                                break;
                            case SDLK_v:
                                if (SDL_GetModState() & KMOD_CTRL)
                                {
                                    inputText = SDL_GetClipboardText();
                                    renderText = true;
                                }
                                break;*/
                        }
                    }
                    /*else if (e.type == SDL_TEXTINPUT)
                    {
                    	if (!(SDL_GetModState() & KMOD_CTRL && (e.text.text[ 0 ] == 'c' || e.text.text[ 0 ] == 'C' || e.text.text[ 0 ] == 'v' || e.text.text[ 0 ] == 'V')) )
                    	{
                    		inputText += e.text.text;
                    		renderText = true;
                    	}
                    }*/
                }

                /*if (renderText)
                {
                	if (inputText != "")
                	{
                		gInputTextTexture.loadFromRenderedText (inputText.c_str(), textColor);
                	}
                	else
                	{
                		gInputTextTexture.loadFromRenderedText (" ", textColor);
                	}
                }*/

                scrollingOffset -= 4;
                if( scrollingOffset < -gBGTexture.getWidth() )
                {
                    scrollingOffset = 0;
                }

                SDL_SetRenderDrawColor (gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
                SDL_RenderClear (gRenderer);

                //Render background
                gBGTexture.render( scrollingOffset, 0 );
                gBGTexture.render( scrollingOffset + gBGTexture.getWidth(), 0 );

                dino.render();

                dino.move(threat1);
                dino.move(threat2);

                //dino.checkCollision(ThreatObject);
                //dino.checkCollision(threat2);

                obstacle1.render();
                obstacle2.render();

                obstacle1.threat_move();
                obstacle2.threat_move();

//                if (dino.checkCollision(threat1) || dino.checkCollision(threat2))
//                {
//                    is_game_over = true;
//                }
//
//
//                if (is_game_over)
//                {
//                    obstacle1.gameOver();
//                    obstacle2.gameOver();
//                }

                if (dino.gameover(obstacle1,obstacle2))
                {
                    obstacle1.gameOver();
                    obstacle2.gameOver();
                }

                threat1 = obstacle1.get_obstacle_1_dimension();
                threat2 = obstacle2.get_obstacle_2_dimension();

                //gPromptTextTexture.render( ( SCREEN_WIDTH - gPromptTextTexture.getWidth() ) / 2, 0 );
                //gInputTextTexture.render( ( SCREEN_WIDTH - gInputTextTexture.getWidth() ) / 2, gPromptTextTexture.getHeight() );

                SDL_RenderPresent (gRenderer);

                if (dino.lose() == true)
                {
                    break;
                }
            }
            //SDL_StopTextInput();
        }
    }

    close();

    return 0;
}

