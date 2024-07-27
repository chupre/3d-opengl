// Standard includes
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

// External
#include <glad/glad.h>

#define SHADER_MAX_PATH 256

extern unsigned int mainShader;
extern unsigned int octreeShader;
extern unsigned int skyboxShader;

void loadShaders();
unsigned int genShader(char* vertexShaderName, char* fragmentShaderName);
char* getShaderContent(const char* fileName);


