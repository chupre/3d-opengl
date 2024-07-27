// Standard includes
#include <string.h>
#include <dirent.h>

// Custom modules
#include <texture.h>
#include <shader.h>
#include <camera.h>

Texture textures[TEXTURES_MAX];
int textures_count = 0;
Skybox skybox;

float skyboxVertices[] = {
    // positions          
    -1.0f,  1.0f, -1.0f,
    -1.0f, -1.0f, -1.0f,
     1.0f, -1.0f, -1.0f,
     1.0f, -1.0f, -1.0f,
     1.0f,  1.0f, -1.0f,
    -1.0f,  1.0f, -1.0f,

    -1.0f, -1.0f,  1.0f,
    -1.0f, -1.0f, -1.0f,
    -1.0f,  1.0f, -1.0f,
    -1.0f,  1.0f, -1.0f,
    -1.0f,  1.0f,  1.0f,
    -1.0f, -1.0f,  1.0f,

     1.0f, -1.0f, -1.0f,
     1.0f, -1.0f,  1.0f,
     1.0f,  1.0f,  1.0f,
     1.0f,  1.0f,  1.0f,
     1.0f,  1.0f, -1.0f,
     1.0f, -1.0f, -1.0f,

    -1.0f, -1.0f,  1.0f,
    -1.0f,  1.0f,  1.0f,
     1.0f,  1.0f,  1.0f,
     1.0f,  1.0f,  1.0f,
     1.0f, -1.0f,  1.0f,
    -1.0f, -1.0f,  1.0f,

    -1.0f,  1.0f, -1.0f,
     1.0f,  1.0f, -1.0f,
     1.0f,  1.0f,  1.0f,
     1.0f,  1.0f,  1.0f,
    -1.0f,  1.0f,  1.0f,
    -1.0f,  1.0f, -1.0f,

    -1.0f, -1.0f, -1.0f,
    -1.0f, -1.0f,  1.0f,
     1.0f, -1.0f, -1.0f,
     1.0f, -1.0f, -1.0f,
    -1.0f, -1.0f,  1.0f,
     1.0f, -1.0f,  1.0f
};

// Load textures and sets up OpenGL
void loadTextures() {
    struct dirent *dirEntry;

    DIR *dir = opendir("../resources/textures");

    if (dir == NULL) {
        return;
    }

    while ((dirEntry = readdir(dir)) != NULL)
        if (strstr(dirEntry->d_name, ".png") != NULL) {
            textures[textures_count] = newTexture(dirEntry->d_name);
            textures_count++;
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
unsigned int loadCubemap(const unsigned char** faces) {
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

void loadSkybox() {
    const unsigned char* faces[] = {
        "../resources/textures/skybox/sky_right.jpg",
        "../resources/textures/skybox/sky_left.jpg",
        "../resources/textures/skybox/sky_top.jpg",
        "../resources/textures/skybox/sky_bottom.jpg",
        "../resources/textures/skybox/sky_front.jpg",
        "../resources/textures/skybox/sky_back.jpg"
    };

    // Loading skybox cubemap 
    skybox.cubemap = loadCubemap(faces);

    // Setting VBO and VAO
    glGenVertexArrays(1, &skybox.VAO);
    glBindVertexArray(skybox.VAO);
    glGenBuffers(1, &skybox.VBO);
    glBindBuffer(GL_ARRAY_BUFFER, skybox.VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(skyboxVertices), skyboxVertices, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (void *)0);
    glEnableVertexAttribArray(0);
}

// Renders skybox
void drawSkybox() {
    glDepthFunc(GL_LEQUAL);
    
    glUseProgram(skyboxShader);

    setProjectionUniform(skyboxShader);
    // Creating view matrix
    mat4 view;
    vec3 temp;
    glm_vec3_add(camera.currPos, camera.front, temp);
    glm_lookat(camera.currPos, temp, camera.up, view);
    mat3 viewtemp;
    glm_mat4_pick3(view, viewtemp);
    glm_mat4_identity(view);
    glm_mat4_ins3(viewtemp, view);

    // Setting view uniform
    int viewLoc = glGetUniformLocation(skyboxShader, "view");
    glUniformMatrix4fv(viewLoc, 1, GL_FALSE, view);

    glBindVertexArray(skybox.VAO);
    glBindTexture(GL_TEXTURE_CUBE_MAP, skybox.cubemap);
    glDrawArrays(GL_TRIANGLES, 0, 36);
    
    glBindVertexArray(0);
    
    glDepthFunc(GL_LESS);
}
