// Standard includes
#include <string.h>
#include <dirent.h>

// Custom modules
#include <texture.h>

Texture textures[TEXTURES_MAX];
int texture_count = 0;
unsigned int skybox;

// Load textures and sets up OpenGL
void loadTextures() {
    const unsigned char* faces[] = {
        "right.jpg",
        "left.jpg",
        "top.jpg",
        "bottom.jpg",
        "front.jpg",
        "back.jpg"
    };
    
    skybox = getCubemapTexture(faces);

    struct dirent *dirEntry;

    DIR *dir = opendir("../resources/textures");

    if (dir == NULL) {
        return;
    }

    while ((dirEntry = readdir(dir)) != NULL)
        if (strstr(dirEntry->d_name, ".png") != NULL) {
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

// Returns a cubemap texture
unsigned int getCubemapTexture(const unsigned char** faces) {
    unsigned int cubemapID;
    glGenTextures(1, &cubemapID);
    glBindTexture(GL_TEXTURE_CUBE_MAP, cubemapID);

    int width, height, channels;
    for (int i = 0; i < CUBE_FACES; i++) {
        unsigned char* pixels = stbi_load(faces[i], &width, &height, &channels, 0);

        if (pixels) {
            glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i,
                         0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, pixels);

            stbi_image_free(pixels);
        }
    }

    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

    return cubemapID;
}
