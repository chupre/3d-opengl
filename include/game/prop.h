#pragma once

// Standard includes
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

// External
#include <glad/glad.h>
#include <cglm/cglm.h>

// Custom modules MAX_PROPS; i
#include <bbox.h>

#define PROP_MAX_VERTICES 64
#define MAX_PROPS 128

extern int active_props;

// Prop struct
typedef struct {
    GLuint VBO, VAO;
    bool hasCollision;
    vec3 offset;
    vec3 pos;
    vec3 vertices[PROP_MAX_VERTICES];
    Bbox bbox;
    mat4 model;
} Prop;

extern Prop* props[MAX_PROPS];

void newProp(Prop* prop, vec3 pos, vec3 offset, bool hasCollision);
void killProp(Prop* prop);
void initPropArray();
