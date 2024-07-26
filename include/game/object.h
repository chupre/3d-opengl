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
#include <texture.h>

#define OBJECT_MAX_VERTICES 64
#define OBJECT_MAX_NODES 64
#define MAX_OBJECTS 128

extern int active_objects;

typedef struct Object Object;

// General object struct
struct Object {
    int VBO, VAO;
    vec3 offset;
    vec3 pos;
    vec3 vertices[OBJECT_MAX_VERTICES];
    Bbox bbox;
    mat4 model;
    bool hasCollision;
    int nodesCount;
    OctreeNode* nodes[OBJECT_MAX_NODES];
    Texture texture;
};

extern Object* objects[MAX_OBJECTS];

void newObject(Object* object, vec3 pos, vec3 offset, bool hasCollision);
void killObject(Object* object);
void initObjectArray();
