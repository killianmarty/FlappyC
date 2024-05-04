#include "cloud.h"

void generateCloud(struct cloud Clouds[MAX_CLOUDS], int * CloudsLen){
	struct cloud * obj = malloc(sizeof(struct cloud));
	obj->x = W_W + CLOUD_WH;
	obj->y = rand() % (W_H - CLOUD_MIN_HEIGHT) + CLOUD_H;
	Clouds[*CloudsLen] = *obj;
	free(obj);
	(*CloudsLen)++;
}


void deleteCloud(struct cloud Clouds[MAX_CLOUDS], int * CloudsLen, int i){
	for(int j = i; j<*CloudsLen - 1; j++){
		Clouds[j]=Clouds[j+1];
	}
	(*CloudsLen)--;
}


void updateClouds(struct cloud Clouds[MAX_CLOUDS], int * CloudsLen, double dt){
	for(int i = 0; i<*CloudsLen; i++){
		Clouds[i].x -= CLOUD_SPEED*dt;
		if(Clouds[i].x < -CLOUD_WH){
			deleteCloud(Clouds, CloudsLen, i);
			i--;
		}
	}
}