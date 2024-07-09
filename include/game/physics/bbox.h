// External
#include <cglm/cglm.h>

// Bounding box struct
#ifndef BBOX_H
#define BBOX_H
typedef struct Bbox {
    vec3 corners[4];
    vec3 min;
    vec3 max;
} Bbox;
#endif