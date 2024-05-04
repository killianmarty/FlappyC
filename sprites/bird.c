#include "bird.h"

void InitBird(struct bird * Bird){
	Bird->x = BIRD_X_DEFAULT;
	Bird->y = BIRD_Y_DEFAULT;
	Bird->vx = 0;
	Bird->vy = 0;
}

void birdGravity(struct bird * Bird, double dt){
	Bird->vy += G*dt;
}

void updateBirdY(struct bird * Bird, double dt){
	Bird->y += Bird->vy*dt;
}

void jumpBird(struct bird * Bird){
	Bird->vy = -JUMP_SPEED;
}

