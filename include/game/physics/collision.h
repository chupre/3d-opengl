// Standard includes
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

// External
#include <cglm/cglm.h>

// Custom modules
#include <bbox.h>

bool collisionDetect(vec3 newPos);
bool AABBcollision(Bbox a, Bbox b);