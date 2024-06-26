#define PROP_VERTICES_SIZE sizeof(float) * 3 * 6
#define PROP_NAME_SIZE 128

// Object struct
typedef struct
{
    GLuint VBO, VAO;
    GLfloat vertices[PROP_VERTICES_SIZE];
    GLchar name[PROP_NAME_SIZE];
} Prop;

// Usage: DYNAMIC - for dynamic draw, STATIC - for static draw
typedef enum { STATIC = GL_STATIC_DRAW, DYNAMIC = GL_DYNAMIC_DRAW } PropType;

void newProp(Prop* PropPtr, GLfloat* vertices, GLchar* name, PropType type);

// Creates Prop VBO and VAO and sets Prop's fields 
void newProp(Prop* PropPtr, GLfloat* vertices, GLchar* name, PropType type)
{
    // Setting vertices and names in Prop
    memcpy(PropPtr->name, name, PROP_NAME_SIZE);
    memcpy(PropPtr->vertices, vertices, PROP_VERTICES_SIZE);

    // Setting VBO and VAO
    glGenVertexArrays(1, &PropPtr->VAO);
    glBindVertexArray(PropPtr->VAO);
    glGenBuffers(1, &PropPtr->VBO);
    glBindBuffer(GL_ARRAY_BUFFER, PropPtr->VBO);
    glBufferData(GL_ARRAY_BUFFER, PROP_VERTICES_SIZE, vertices, type);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (void*)0);
    glEnableVertexAttribArray(0);

    // Unbinding for safety
    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}
