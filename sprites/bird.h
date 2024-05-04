#ifndef BIRD
#define BIRD

#include "../globals/utils.h"


struct bird {
	double x;
	double y;
	double vx;
	double vy;
};


void InitBird(struct bird * Bird);

void birdGravity(struct bird * Bird, double dt);

void updateBirdY(struct bird * Bird, double dt);

void jumpBird(struct bird * Bird);

#endif
