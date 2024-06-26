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
