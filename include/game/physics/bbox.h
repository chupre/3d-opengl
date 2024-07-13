#pragma once

#define TopLeftFront 0
#define TopRightFront 1
#define BottomRightFront 2
#define BottomLeftFront 3
#define TopLeftBack 4
#define TopRightBack 5
#define BottomRightBack 6
#define BottomLeftBack 7

// External
#include <cglm/cglm.h>

// Bounding box struct
typedef struct Bbox {
    vec3 min;
    vec3 max;
} Bbox;