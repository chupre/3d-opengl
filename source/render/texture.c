// Standard includes
#include <string.h>
#include <dirent.h>

// Custom modules
#include <texture.h>

Texture default_texture;
Texture textures[TEXTURES_MAX];
int texture_count = 0;

// Load textures and sets up OpenGL
void loadTextures() {
    stbi_set_flip_vertically_on_load(1);

    default_texture = newTexture("default.png");

    struct dirent *dirEntry;

    DIR *dir = opendir("../resources/textures");

    if (dir == NULL) {
        return;
    }

    while ((dirEntry = readdir(dir)) != NULL)
        if (strcmp(dirEntry->d_name, ".") != 0 && 
            strcmp(dirEntry->d_name, "..") && 
            strcmp(dirEntry->d_name, "default.png")) {
                textures[texture_count] = newTexture(dirEntry->d_name);
                texture_count++;
            }

    closedir(dir);
}

// Creates a texture instance
Texture newTexture(unsigned char* image_name) {
    Texture texture;

    // Setting texture image path
    char full_path[TEXTURE_PATH_SIZE] = "../resources/textures/";
    strcat(full_path, image_name);

    // Copying image path to texture struct
    strcpy(texture.name, image_name);

    // Loading image
    texture.pixels = stbi_load(full_path, &texture.width, &texture.height, &texture.channels, 0);

    // Setting texture in OpenGL
    glGenTextures(1, &texture.glName);
    glBindTexture(GL_TEXTURE_2D, texture.glName);

    // Texture wrapping
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    
    // Setting texture filtering
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, texture.width, texture.height, 0, GL_RGB, GL_UNSIGNED_BYTE, texture.pixels);
    glGenerateMipmap(GL_TEXTURE_2D);

    // Freeing allocated space for image
    stbi_image_free(texture.pixels);

    return texture;
}