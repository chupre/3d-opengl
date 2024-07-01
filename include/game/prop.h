// Standard includes
#include <string.h>
#include <stdlib.h>

// External
#include <glad/glad.h>

#define PROP_VERTICES_SIZE sizeof(float) * 3 * 6
#define PROP_NAME_SIZE 128

// Object struct
typedef struct
{
    GLuint VBO, VAO;
    GLint ID;
    GLfloat vertices[PROP_VERTICES_SIZE];
    GLchar name[PROP_NAME_SIZE];
} Prop;

// Usage: DYNAMIC - for dynamic draw, STATIC - for static draw
typedef enum { STATIC = GL_STATIC_DRAW, DYNAMIC = GL_DYNAMIC_DRAW } PropType;

extern Prop* props;
extern GLint propCount;
extern GLint propID;

void newProp(GLfloat* vertices, GLchar* name, PropType type);
void initPropArray();
void killProp(GLint ID);