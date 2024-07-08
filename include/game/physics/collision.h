// Standard includes
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

// External
#include <cglm/cglm.h>

// Custom modules
#include <prop.h>

bool collisionDetect(vec3 newPos);
bool AABBcollision(vec3 bbox_1[4], vec3 bbox_2[4]);