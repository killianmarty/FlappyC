#ifndef TUBE 
#define TUBE

#include "../globals/utils.h"
#include <stdlib.h>

struct tube{
	double x;
	double holeY;
	int passed;
};

void generateTube(struct tube Tubes[MAX_TUBES], int * TubesLen);

void deleteTube(struct tube Tubes[MAX_TUBES], int * TubesLen, int i);

void updateTubes(struct tube Tubes[MAX_TUBES], int * TubesLen, double dt);

#endif