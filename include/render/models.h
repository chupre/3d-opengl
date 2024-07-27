// External
#include <cglm/cglm.h>

// Custom modules
#include <texture.h>

typedef struct Vertex {
    vec3 position;
    vec3 normal;
    vec2 texCoords;
} Vertex;

typedef struct Mesh {
    Vertex* vertices;
    Texture* textures;
    unsigned int* indices;
    unsigned int VAO, VBO, EBO;
} Mesh;

Mesh newMesh(Vertex* vertices, Texture* textures, unsigned int* indices);