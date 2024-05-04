#include <time.h>
#include <unistd.h>
#include <stdlib.h>

#include "globals/utils.h"
#include "render/renderer.h"
#include "sprites/bird.h"
#include "sprites/cloud.h"
#include "sprites/tube.h"
#include "sprites/poop.h"
#include "engine/engine.h"

int main() {
    //SDL Init
    SDL_Init(SDL_INIT_VIDEO);
    SDL_Window *fenetre = SDL_CreateWindow("Flappy C", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, W_W, W_H, SDL_WINDOW_SHOWN);
    SDL_Renderer *renderer = SDL_CreateRenderer(fenetre, -1, SDL_RENDERER_ACCELERATED);
    if(SDL_GL_SetSwapInterval(-1) == -1) SDL_GL_SetSwapInterval(1);

    //TTF Init
    TTF_Init();
    TTF_Font * police = TTF_OpenFont("assets/font.ttf", 28);

    //Image init
    struct tubeImg TbIMG;
    SDL_Texture * flappyTexture;
    SDL_Texture * cloudTexture;
    loadImages(renderer, &TbIMG, &flappyTexture, &cloudTexture);

    //Random init
    srand(time(NULL));
	
	//clock init
	struct timespec end;
	struct timespec start;

    //VARIABLES
    struct bird Flappy;
    InitBird(&Flappy);

    struct tube Tubes[MAX_TUBES];
    int TubesLen = 0;

    struct cloud Clouds[MAX_CLOUDS];
    int CloudsLen = 0;

    struct poop Poop;
    Poop.active = 0;

    int score = 0;

    //Main loop
    SDL_Event event;
    int run = 1;
    double fps = 60;
    double dt = 1000/fps;
    while (run) {
    	clock_gettime(CLOCK_MONOTONIC,&start);
        while (SDL_PollEvent(&event) != 0) {
            if (event.type == SDL_QUIT) {
                run = 0;
            } else if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_SPACE) {
                jumpBird(&Flappy);
            }
        }


        //generating tubes
        if(((rand()%(int)(fps)==0) && (TubesLen == 0 || Tubes[TubesLen-1].x <= W_WH) && (TubesLen < MAX_TUBES))) generateTube(Tubes, &TubesLen);

        //generating clouds
        if(((rand()%(int)(2*fps)==0) && (CloudsLen == 0 || Clouds[CloudsLen-1].x <= W_WH) && (CloudsLen < MAX_CLOUDS))) generateCloud(Clouds, &CloudsLen);

        //generating poop
        if(rand()%(int)(20*fps)==0 && !Poop.active) BirdPoop(&Poop, Flappy.y, Flappy.vy);

        //Motion management
        if(Poop.active){
        	poopGravity(&Poop, dt);
        	updatePoopY(&Poop, dt);
        }
        birdGravity(&Flappy, dt);
        updateBirdY(&Flappy, dt);
        updateTubes(Tubes, &TubesLen, dt);
        updateClouds(Clouds, &CloudsLen, dt);

        //Collides management
        if(outOfBounds(&Flappy)) run = 0;
        if(collides(&Flappy, Tubes, TubesLen, &score)) run = 0;

        //Rendering
		resetRender(renderer);
		renderPoop(renderer, &Poop);
		renderClouds(renderer, Clouds, CloudsLen, cloudTexture);
        renderBird(renderer, &Flappy, flappyTexture);
        renderTubes(renderer, Tubes, TubesLen, &TbIMG);
        renderScore(renderer, police, score);

        SDL_RenderPresent(renderer);

        //Processing delta
        clock_gettime(CLOCK_MONOTONIC,&end);
        long deltatime = (long)calculateDeltaTime(end, start);

        //Delay normalisation
        double delay = 1000000.0/(double)MAX_FPS - deltatime;
        if(delay < 0) delay = 0.0;
        usleep(delay);
    }
    gameOver(renderer, police);

    // Free ressources
    TTF_CloseFont(police);
    SDL_DestroyTexture(flappyTexture);
    SDL_DestroyTexture(cloudTexture);
    SDL_DestroyTexture(TbIMG.pipebaseInvert);
    SDL_DestroyTexture(TbIMG.pipebaseNormal);
    SDL_DestroyTexture(TbIMG.pipetopInvert);
    SDL_DestroyTexture(TbIMG.pipetopNormal);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(fenetre);
    TTF_Quit();
    IMG_Quit();
    SDL_Quit();

    return 0;
}