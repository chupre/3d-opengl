#define OBJECT_VERTICES_SIZE sizeof(float) * 3 * 6
#define OBJECT_NAME_SIZE 128

// Object struct
typedef struct
{
    GLuint VBO, VAO;
    GLfloat vertices[OBJECT_VERTICES_SIZE];
    GLchar name[OBJECT_NAME_SIZE];
} object;

// Usage: DYNAMIC - for dynamic draw, STATIC - for static draw
typedef enum { STATIC = GL_STATIC_DRAW, DYNAMIC = GL_DYNAMIC_DRAW } objectType;

void newObject(object* objectPtr, GLfloat* vertices, GLchar* name, objectType type);

// Creates object VBO and VAO and sets object's fields 
void newObject(object* objectPtr, GLfloat* vertices, GLchar* name, objectType type)
{
    // Setting vertices and names in object
    memcpy(objectPtr->name, name, OBJECT_NAME_SIZE);
    memcpy(objectPtr->vertices, vertices, OBJECT_VERTICES_SIZE);

    // Setting VBO and VAO
    glGenVertexArrays(1, &objectPtr->VAO);
    glBindVertexArray(objectPtr->VAO);
    glGenBuffers(1, &objectPtr->VBO);
    glBindBuffer(GL_ARRAY_BUFFER, objectPtr->VBO);
    glBufferData(GL_ARRAY_BUFFER, OBJECT_VERTICES_SIZE, vertices, type);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (void*)0);
    glEnableVertexAttribArray(0);

    // Unbinding for safety
    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}
