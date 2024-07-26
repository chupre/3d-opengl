#pragma once

// External
#include <stb/stb_image.h>
#include <glad/glad.h>

#define TEXTURE_PATH_SIZE 256
#define TEXTURES_MAX 256

typedef struct Texture { 
    int width;
    int height;
    int channels;
    unsigned int glName;
    unsigned char* pixels;
    unsigned char name[TEXTURE_PATH_SIZE];
} Texture;

extern Texture default_texture;
extern Texture textures[TEXTURES_MAX];
extern int texture_count;

void loadTextures();
Texture newTexture(unsigned char* image_name);