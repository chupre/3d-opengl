#define PROP_VERTICES_SIZE sizeof(float) * 3 * 6
#define PROP_NAME_SIZE 128

// Object struct
typedef struct
{
    GLuint VBO, VAO;
    GLfloat vertices[PROP_VERTICES_SIZE];
    GLchar name[PROP_NAME_SIZE];
} prop;

// Usage: DYNAMIC - for dynamic draw, STATIC - for static draw
typedef enum { STATIC = GL_STATIC_DRAW, DYNAMIC = GL_DYNAMIC_DRAW } propType;

void newProp(prop* propPtr, GLfloat* vertices, GLchar* name, propType type);

// Creates prop VBO and VAO and sets prop's fields 
void newProp(prop* propPtr, GLfloat* vertices, GLchar* name, propType type)
{
    // Setting vertices and names in prop
    memcpy(propPtr->name, name, PROP_NAME_SIZE);
    memcpy(propPtr->vertices, vertices, PROP_VERTICES_SIZE);

    // Setting VBO and VAO
    glGenVertexArrays(1, &propPtr->VAO);
    glBindVertexArray(propPtr->VAO);
    glGenBuffers(1, &propPtr->VBO);
    glBindBuffer(GL_ARRAY_BUFFER, propPtr->VBO);
    glBufferData(GL_ARRAY_BUFFER, PROP_VERTICES_SIZE, vertices, type);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (void*)0);
    glEnableVertexAttribArray(0);

    // Unbinding for safety
    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}
