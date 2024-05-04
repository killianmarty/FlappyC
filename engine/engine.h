#include "../globals/utils.h"
#include "../sprites/bird.h"
#include "../sprites/tube.h"

#include <time.h>
#include <stdlib.h>
#include <unistd.h>

int outOfBounds(struct bird * Bird);
int collides(struct bird * Bird, struct tube Tubes[MAX_TUBES], int TubesLen, int * score);
int64_t calculateDeltaTime(struct timespec after, struct timespec before);