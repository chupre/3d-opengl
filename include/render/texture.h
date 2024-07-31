#pragma once

// External
#include <stb/stb_image.h>
#include <glad/glad.h>
// #include <cglm/cglm.h>

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

typedef struct Skybox {
    unsigned int VBO, VAO;
    unsigned int cubemap;
} Skybox;

extern Texture textures[TEXTURES_MAX];
extern int textures_count;
extern Skybox skybox;

void loadTextures();
void loadSkybox();
void drawSkybox();
unsigned int loadCubemap(const unsigned char** faces);
Texture newTexture(unsigned char* image_name);
