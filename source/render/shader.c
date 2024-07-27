// Custom modules
#include <shader.h>

unsigned int mainShader;
unsigned int octreeShader;

// Parse shader code in string
char* getShaderContent(const GLchar* fileName) {
    FILE* shaderFile;
    long size = 0;
    char* shaderContent;

    shaderFile = fopen(fileName, "r");

    if (shaderFile == NULL)
        printf("Failed to open %s\n", fileName);

    fseek(shaderFile, 0, SEEK_END);
    size = ftell(shaderFile);
    rewind(shaderFile);

    shaderContent = memset(malloc(size + 1), '\0', size + 1);
    fread(shaderContent, 1, size, shaderFile);
    fclose(shaderFile);

    return shaderContent;
}

// Returns shader
unsigned int genShader(char* vertexShaderName, char* fragmentShaderName) {
    // Constructing file paths
    char vertexShaderFullPath[SHADER_MAX_PATH] = "../source/shaders/";
    char fragmentShaderFullPath[SHADER_MAX_PATH] = "../source/shaders/";
    strcat(vertexShaderFullPath, vertexShaderName);
    strcat(fragmentShaderFullPath, fragmentShaderName);
    strcat(vertexShaderFullPath, ".glsl");
    strcat(fragmentShaderFullPath, ".glsl");

    const char* vertexShaderSource = getShaderContent(vertexShaderFullPath);
    const char* fragmentShaderSource = getShaderContent(fragmentShaderFullPath);

    unsigned int vertexShader;
    vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    glCompileShader(vertexShader);

    unsigned int fragmentShader;
    fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    glCompileShader(fragmentShader);

    unsigned int shader = glCreateProgram();
    glAttachShader(shader, vertexShader);
    glAttachShader(shader, fragmentShader);
    glLinkProgram(shader);

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    return shader;
}

void loadShaders() {
    mainShader = genShader("vMain", "fMain");
    octreeShader = genShader("vOctree", "fOctree");
}