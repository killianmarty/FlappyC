#include "tube.h"

void generateTube(struct tube Tubes[MAX_TUBES], int * TubesLen){
	struct tube * obj = malloc(sizeof(struct tube));
	obj->x = W_W + TUBE_WH;
	obj->holeY = rand() % (W_H - TUBE_HOLE_H - 2*TUBE_HOLE_MARGIN) + TUBE_HOLE_HH + TUBE_HOLE_MARGIN;
	obj->passed = 0;
	Tubes[*TubesLen] = *obj;
	free(obj);
	(*TubesLen)++;
}


void deleteTube(struct tube Tubes[MAX_TUBES], int * TubesLen, int i){
	for(int j = i; j<*TubesLen - 1; j++){
		Tubes[j] = Tubes[j+1];
	}
	(*TubesLen)--;
}


void updateTubes(struct tube Tubes[MAX_TUBES], int * TubesLen, double dt){
	for(int i = 0; i<*TubesLen; i++){
		Tubes[i].x -= TUBE_SPEED*dt;
		if(Tubes[i].x < -TUBE_WH){ //delete Tube
			deleteTube(Tubes, TubesLen, i);
			i--;
		}
	}
}