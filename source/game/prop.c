// Custom modules
#include <prop.h>

Prop *props;
GLint propCount = 0;
GLint propID = 0;

// Creates prop VBO and VAO and sets prop's fields
void newProp(GLfloat *vertices, GLchar *name, PropType type, bool hasCollision)
{
    // Allocating more memory to prop array
    if (propCount != 0)
    {
        props = realloc(props, sizeof(Prop) * (propCount + 1));
    }

    // Setting unique ID for prop
    props[propCount].ID = propID;
    propID++;

    props[propCount].hasCollision = hasCollision;

    // Setting vertices and names in prop
    memcpy(props[propCount].name, name, PROP_NAME_SIZE);
    memcpy(props[propCount].vertices, vertices, PROP_VERTICES_SIZE);

    // Setting VBO and VAO
    glGenVertexArrays(1, &props[propCount].VAO);
    glBindVertexArray(props[propCount].VAO);
    glGenBuffers(1, &props[propCount].VBO);
    glBindBuffer(GL_ARRAY_BUFFER, props[propCount].VBO);
    glBufferData(GL_ARRAY_BUFFER, PROP_VERTICES_SIZE, vertices, type);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (void *)0);
    glEnableVertexAttribArray(0);

    // Unbinding for safety
    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    propCount++;
}

// Allocating memory for props' array
void initPropArray()
{
    props = malloc(sizeof(Prop));
}

// Freeing memory for prop
void killProp(GLint ID)
{
    GLint currPropIndex = -1;

    // Searching for a prop to kill
    for (int i = 0; i < propCount; i++)
    {
        if (props[i].ID == ID)
        {
            currPropIndex = i;
            break;
        }
    }

    // Deleting prop and moving array
    if (currPropIndex != -1)
    {
        for (int i = currPropIndex; i < propCount - 1; i++)
        {
            memcpy(&props[i], &props[i + 1], sizeof(Prop));
        }

        propCount--;
        props = realloc(props, sizeof(Prop) * propCount);
    }
}