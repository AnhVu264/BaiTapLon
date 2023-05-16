#ifndef GAME_H
#define GAME_H

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <SDL_ttf.h>
#include <iostream>
#include <cstring>

using namespace std;

/*class Text
{
    public:
        TextObj();
        ~TextObj();

        enum ColorText
        {
            white_Text = 0,
            black_Text = 1,
        };

        bool loadFromRenderText (TTF_FONT* font, SDL_Renderer* screen);
        void free();


        void setColor (Uint8 red, Uint8 green, Uint8 blue);
        void setColor (int type);

        void RenderText (SDL_Renderer* screen,
                         TEXT_pos_x, TEXT_pos_y,
                         SDL_Rect* clip = NULL,
                         double angle = 0.0,
                         SDL_Point* center = NULL,
                         SDL_RendererFlip flip = SDL_FLIP_NONE);
        int GetWidth() const {return width_Text;}
        int GetHeight() const {return height_Text;}
        void SetText(const string& text) {str_value_ = text;}
        string GetText() const {return str_value_;}

    private:
        int TEXT_pos_x, TEXT_pos_y;
        int width_Text;
        int height_Text;
        SDL_Color color_Text;
        SDL_Texture* texture_;
        string str_value_;
};
*/


//Texture wrapper class
class LTexture
{
    public:
        //Initializes variables
        LTexture();

        //Deallocates memory
        ~LTexture();

        //Loads image at specified path
        bool loadFromFile( string path );

#if defined(SDL_TTF_MAJOR_VERSION)
        //Creates image from font string
        bool loadFromRenderedText( std::string textureText, SDL_Color textColor );
#endif

        void free();

        //Set color modulation
        void setColor( Uint8 red, Uint8 green, Uint8 blue );

        //Set blending
        void setBlendMode( SDL_BlendMode blending );

        //Set alpha modulation
        void setAlpha( Uint8 alpha );

        //Renders texture at given point
        void render( int x, int y, SDL_Rect* clip = NULL, double angle = 0.0, SDL_Point* center = NULL, SDL_RendererFlip flip = SDL_FLIP_NONE );

        //Gets image dimensions
        SDL_Texture* getTexture();
        int getWidth();
        int getHeight();

    private:
        //The actual hardware texture
        SDL_Texture* mTexture;

        //Image dimensions
        int mWidth;
        int mHeight;
};

extern SDL_Window* gWindow;

extern SDL_Renderer* gRenderer;

extern LTexture gPromptTexture;

extern Mix_Music* gMusic;

/*
extern TTF_Font *gFont;

extern LTexture gPromptTextTexture;

extern LTexture gInputTextTexture;
*/


#endif //GAME_H
