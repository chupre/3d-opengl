// Standard includes
#include <string.h>

// Custom modules
#include <texture.h>

Texture default_texture;

// Load textures and sets up OpenGL
void initTextures() {
    // Texture wrapping
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);
    
    // Setting texture filtering
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    default_texture = newTexture("default");
}

// Creates a texture instance
Texture newTexture(unsigned char* image_name) {
    Texture texture;

    // Setting texture image path
    char full_path[TEXTURE_PATH_SIZE] = "../resources/textures/";
    strcat(full_path, image_name);
    strcat(full_path, ".png"); 

    // Loading image
    texture.pixels = stbi_load(full_path, &texture.width, &texture.height, &texture.channels, 0);

    // Setting texture in OpenGL
    glGenTextures(1, &texture.glName);
    glBindTexture(GL_TEXTURE_2D, texture.glName);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, texture.width, texture.height, 0, GL_RGB, GL_UNSIGNED_BYTE, texture.pixels);
    glGenerateMipmap(GL_TEXTURE_2D);

    // Freeing allocated space for image
    stbi_image_free(texture.pixels);

    return texture;
}