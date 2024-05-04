#include "engine.h"

int outOfBounds(struct bird * Bird){
	return (Bird->y > W_H || Bird->y < 0);
}

int collides(struct bird * Bird, struct tube Tubes[MAX_TUBES], int TubesLen, int * score){
	for(int i = 0; i<TubesLen; i++){
		if(Tubes[i].x - TUBE_WH < BIRD_X_DEFAULT + BIRD_WH && Tubes[i].x + TUBE_WH > BIRD_X_DEFAULT - BIRD_WH){
			if(Bird->y - BIRD_HH < Tubes[i].holeY - TUBE_HOLE_HH || Bird->y + BIRD_HH > Tubes[i].holeY + TUBE_HOLE_HH){
				//collide
				return 1;
			}else if(Tubes[i].x + TUBE_WH < BIRD_X_DEFAULT + BIRD_WH){
				//passed
				if(!Tubes[i].passed){
					(*score)++;
					Tubes[i].passed = 1;
				}
			}
		}
	}
	return 0;
}

int64_t calculateDeltaTime(struct timespec after, struct timespec before){
    return ((int64_t)after.tv_sec - (int64_t)before.tv_sec) * (int64_t)1000000 + ((int64_t)after.tv_nsec - (int64_t)before.tv_nsec) / 1000;
}