#pragma once

// External
#include <stb/stb_image.h>
#include <glad/glad.h>

#define TEXTURE_PATH_SIZE 256

typedef struct Texture { 
    int width;
    int height;
    int channels;
    unsigned int glName;
    unsigned char* pixels;
} Texture;

extern Texture default_texture;

void initTextures();
Texture newTexture(unsigned char* image_name);