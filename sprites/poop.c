#include "poop.h"

void BirdPoop(struct poop * Poop, double birdY, double birdVy){
	Poop->y = birdY;
	Poop->vy = birdVy;
	Poop->active = 1;
}


void poopGravity(struct poop * Poop, double dt){
	Poop->vy += G*dt;
}

void updatePoopY(struct poop * Poop, double dt){
	Poop->y += Poop->vy*dt;
	if(Poop->y > W_H) Poop->active=0;
}