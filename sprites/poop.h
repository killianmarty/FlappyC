#ifndef POOP
#define POOP

#include "../globals/utils.h"

struct poop{
	double y;
	double vy;
	int active;
};

void BirdPoop(struct poop * Poop, double birdY, double birdVy);

void poopGravity(struct poop * Poop, double dt);

void updatePoopY(struct poop * Poop, double dt);

#endif