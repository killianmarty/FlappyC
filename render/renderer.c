#include "renderer.h"

void loadImages(SDL_Renderer * renderer, struct tubeImg * TbIMG, SDL_Texture ** flappyTexture, SDL_Texture ** cloudTexture){
	TbIMG->pipebaseInvert = IMG_LoadTexture(renderer, "assets/pipebase_inverted.png");
    TbIMG->pipebaseNormal = IMG_LoadTexture(renderer, "assets/pipebase_normal.png");
    TbIMG->pipetopInvert = IMG_LoadTexture(renderer, "assets/pipetop_inverted.png");
    TbIMG->pipetopNormal = IMG_LoadTexture(renderer, "assets/pipetop_normal.png");
    *flappyTexture = IMG_LoadTexture(renderer, "assets/flappy.png");
    *cloudTexture = IMG_LoadTexture(renderer, "assets/cloud.png");
}

void resetRender(SDL_Renderer * renderer){
    SDL_SetRenderDrawColor(renderer, 66, 209, 245, 255);
    SDL_RenderClear(renderer);
}

void renderBird(SDL_Renderer * renderer, struct bird * Bird, SDL_Texture * birdTexture){
    SDL_Rect rectangle = {Bird->x - BIRD_WH, Bird->y - BIRD_HH, BIRD_W, BIRD_H};
    SDL_RenderCopy(renderer, birdTexture, NULL, &rectangle);
}

void renderTubes(SDL_Renderer * renderer, struct tube * Tubes, int TubesLen, struct tubeImg * TbIMG){
    SDL_SetRenderDrawColor(renderer, 33, 156, 26, 255);
    for(int i = 0; i<TubesLen; i++){
        SDL_Rect rect1 = {Tubes[i].x - TUBE_WH, 0, TUBE_W, Tubes[i].holeY - TUBE_HOLE_HH - TUBE_TOP_H};
        SDL_Rect rect2 = {Tubes[i].x - TUBE_WH, Tubes[i].holeY + TUBE_HOLE_HH + TUBE_TOP_H, TUBE_W, W_H - Tubes[i].holeY - TUBE_HOLE_HH};
        SDL_Rect rect3 = {Tubes[i].x - TUBE_WH, Tubes[i].holeY - TUBE_HOLE_HH - TUBE_TOP_H, TUBE_W, TUBE_TOP_H};
        SDL_Rect rect4 = {Tubes[i].x - TUBE_WH, Tubes[i].holeY + TUBE_HOLE_HH, TUBE_W, TUBE_TOP_H};
        SDL_RenderCopy(renderer, TbIMG->pipebaseInvert, NULL, &rect1);
        SDL_RenderCopy(renderer, TbIMG->pipebaseNormal, NULL, &rect2);
        SDL_RenderCopy(renderer, TbIMG->pipetopInvert, NULL, &rect3);
        SDL_RenderCopy(renderer, TbIMG->pipetopNormal, NULL, &rect4);
    }
}

void renderClouds(SDL_Renderer * renderer, struct cloud Clouds[MAX_CLOUDS], int CloudsLen, SDL_Texture * cloudTexture){
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    for(int i = 0; i<CloudsLen; i++){
        SDL_Rect rect = {Clouds[i].x - CLOUD_WH, Clouds[i].y - CLOUD_HH, CLOUD_W, CLOUD_H};
        SDL_RenderCopy(renderer, cloudTexture, NULL, &rect);
    }
}

void renderPoop(SDL_Renderer * renderer, struct poop * Poop){
    if(Poop->active){
        SDL_SetRenderDrawColor(renderer, 107, 69, 31, 255);
        SDL_Rect rectangle = {BIRD_X_DEFAULT - POOP_SIZE_H, Poop->y - POOP_SIZE_H, POOP_SIZE, POOP_SIZE};
        SDL_RenderFillRect(renderer, &rectangle);
    }   
}

void renderGameOverText(SDL_Renderer *renderer, TTF_Font *police, char text[]){
    SDL_Color textColor = {0, 0, 0, 255};

    SDL_Surface *textSurface = TTF_RenderText_Solid(police, text, textColor);
    SDL_Texture *textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);
    SDL_FreeSurface(textSurface);

    int textW, textH;
    SDL_QueryTexture(textTexture, NULL, NULL, &textW, &textH);

    SDL_Rect textPosition = {W_WH - textW/2, W_HH - textH/2, textW, textH};

    SDL_RenderCopy(renderer, textTexture, NULL, &textPosition);
    SDL_DestroyTexture(textTexture);
}

void renderScore(SDL_Renderer *renderer, TTF_Font *police, int score) {
    char textScore[20];
    SDL_Color textColor = {0, 0, 0, 0};
    snprintf(textScore, sizeof(textScore), "Score : %d", score);

    SDL_Surface *textSurface = TTF_RenderText_Solid(police, textScore, textColor);
    SDL_Texture *textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);
    SDL_FreeSurface(textSurface);

    int textW, textH;
    SDL_QueryTexture(textTexture, NULL, NULL, &textW, &textH);

    SDL_Rect textPosition = {10, 10, textW, textH}; // Position du texte

    SDL_RenderCopy(renderer, textTexture, NULL, &textPosition);
    SDL_DestroyTexture(textTexture);
}

void gameOver(SDL_Renderer * renderer, TTF_Font * police){
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    char text[] = "Game Over";
    renderGameOverText(renderer, police, text);
    SDL_RenderPresent(renderer);
    
    int quit = 0;
    SDL_Event event;
    while(!quit){
    	while (SDL_PollEvent(&event) != 0) {
	        if (event.type == SDL_QUIT || event.type == SDL_KEYDOWN) {
                quit = 1;
            }
	    }
    } 
}