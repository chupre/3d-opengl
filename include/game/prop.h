#pragma once

// Standard includes
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

// External
#include <glad/glad.h>
#include <cglm/cglm.h>

// Custom modules
#include <bbox.h>
#include <octree.h>

#define PROP_MAX_VERTICES 64
#define PROP_MAX_NODES 64
#define MAX_PROPS 128

extern int active_props;

typedef struct Prop Prop;

// General prop struct
struct Prop {
    int VBO, VAO;
    vec3 offset;
    vec3 pos;
    vec3 vertices[PROP_MAX_VERTICES];
    Bbox bbox;
    mat4 model;
    bool isPlayer;
    bool hasCollision;
    int nodesCount;
    OctreeNode* nodes[PROP_MAX_NODES];
};

extern Prop* props[MAX_PROPS];

void newProp(Prop* prop, vec3 pos, vec3 offset, bool hasCollision);
void killProp(Prop* prop);
void initPropArray();
