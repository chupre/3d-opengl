// Custom modules
#include <prop.h>

Prop* props[MAX_PROPS];

// Creates prop VBO and VAO and sets prop's fields
void newProp(Prop* prop, vec3 pos, vec3 offset, bool hasCollision)
{
    // Setting pointer in props array
    for (int i = 0; i < MAX_PROPS; i++)
    {
        if (props[i] == NULL)
        {
            props[i] = prop;
            break;
        }
    }

    prop->hasCollision = hasCollision;

    // Setting vertices and names in prop
    GLfloat x = pos[0] + offset[0];
    GLfloat y = pos[1] + offset[1];
    GLfloat z = pos[2] + offset[2];
    GLfloat propVertices[] = 
    {
    -x, -y, -z,
     x, -y, -z,
     x,  y, -z,
     x,  y, -z,
    -x,  y, -z,
    -x, -y, -z,

    -x, -y,  z,
     x, -y,  z,
     x,  y,  z,
     x,  y,  z,
    -x,  y,  z,
    -x, -y,  z,

    -x,  y,  z,
    -x,  y, -z,
    -x, -y, -z,
    -x, -y, -z,
    -x, -y,  z,
    -x,  y,  z,

     x,  y,  z,
     x,  y, -z,
     x, -y, -z,
     x, -y, -z,
     x, -y,  z,
     x,  y,  z,

    -x, -y, -z,
     x, -y, -z,
     x, -y,  z,
     x, -y,  z,
    -x, -y,  z,
    -x, -y, -z,

    -x,  y, -z,
     x,  y, -z,
     x,  y,  z,
     x,  y,  z,
    -x,  y,  z,
    -x,  y, -z,
    };
    memcpy(prop->vertices, propVertices, sizeof(propVertices));

    // Setting VBO and VAO
    glGenVertexArrays(1, &prop->VAO);
    glBindVertexArray(prop->VAO);
    glGenBuffers(1, &prop->VBO);
    glBindBuffer(GL_ARRAY_BUFFER, prop->VBO);
    glBufferData(GL_ARRAY_BUFFER, PROP_MAX_VERTICES * sizeof(vec3), prop->vertices, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (void *)0);
    glEnableVertexAttribArray(0);

    // Unbinding for safety
    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

// Null the prop array
void initPropArray()
{
    for (int i = 0; i < MAX_PROPS; i++)
    {
        props[i] = NULL;
    }
}

// Freeing memory for prop
void killProp(Prop* prop)
{
    for (int i = 0; i < MAX_PROPS; i++)
    {
        if (props[i] == prop)
        {
            props[i] = NULL;
            return;
        }
    }
}