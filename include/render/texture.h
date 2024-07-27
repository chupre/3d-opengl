#pragma once

// External
#include <stb/stb_image.h>
#include <glad/glad.h>

#define TEXTURE_PATH_SIZE 256
#define TEXTURES_MAX 256
#define CUBE_FACES 6

typedef struct Texture { 
    int width;
    int height;
    int channels;
    unsigned int glName;
    unsigned char* pixels;
    unsigned char name[TEXTURE_PATH_SIZE];
} Texture;

extern Texture textures[TEXTURES_MAX];
extern int texture_count;
extern unsigned int skybox;

void loadTextures();
unsigned int getCubemapTexture(const unsigned char** faces);
Texture newTexture(unsigned char* image_name);