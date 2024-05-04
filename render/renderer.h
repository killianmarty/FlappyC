#ifndef RENDER 
#define RENDER

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>
#include "../globals/utils.h"
#include "../sprites/bird.h"
#include "../sprites/cloud.h"
#include "../sprites/tube.h"
#include "../sprites/poop.h"

struct tubeImg{
	SDL_Texture * pipebaseInvert;
	SDL_Texture * pipebaseNormal;
	SDL_Texture * pipetopInvert;
	SDL_Texture * pipetopNormal;
};

void loadImages(SDL_Renderer * renderer, struct tubeImg * TbIMG, SDL_Texture ** flappyTexture, SDL_Texture ** cloudTexture);
void resetRender(SDL_Renderer * renderer);
void renderBird(SDL_Renderer * renderer, struct bird * Bird, SDL_Texture * birdTexture);
void renderTubes(SDL_Renderer * renderer, struct tube * Tubes, int TubesLen, struct tubeImg * TbIMG);
void renderClouds(SDL_Renderer * renderer, struct cloud Clouds[MAX_CLOUDS], int CloudsLen, SDL_Texture * cloudTexture);
void renderPoop(SDL_Renderer * renderer, struct poop * Poop);
void renderGameOverText(SDL_Renderer *renderer, TTF_Font *police, char text[]);
void renderScore(SDL_Renderer *renderer, TTF_Font *police, int score);
void gameOver(SDL_Renderer * renderer, TTF_Font * police);

#endif