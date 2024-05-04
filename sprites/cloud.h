#ifndef CLOUD 
#define CLOUD

#include "../globals/utils.h"
#include <stdlib.h>

struct cloud{
	double x;
	double y;
};

void generateCloud(struct cloud Clouds[MAX_CLOUDS], int * CloudsLen);

void deleteCloud(struct cloud Clouds[MAX_CLOUDS], int * CloudsLen, int i);

void updateClouds(struct cloud Clouds[MAX_CLOUDS], int * CloudsLen, double dt);

#endif