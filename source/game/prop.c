// Custom modules
#include <prop.h>
#include <camera.h>
#include <vector.h>

Prop* props[MAX_PROPS];
int active_props = 0;

// Creates prop VBO and VAO and sets prop's fields
void newProp(Prop* prop, vec3 pos, vec3 offset, bool hasCollision) {
    bool propCreated = false;

    // Setting pointer in props array
    for (int i = 0; i < MAX_PROPS; i++)
    {
        if (props[i] == NULL)
        {
            props[i] = prop;
            propCreated = true;
            break;
        }
    }

    // Check if there was a free space for the prop
    if (!propCreated)
        return;

    // Setting vertices in prop
    GLfloat x = offset[0];
    GLfloat y = offset[1];
    GLfloat z = offset[2];
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
    memcpy(prop->offset, offset, sizeof(vec3));
    memcpy(prop->pos, pos, sizeof(vec3));

    for (int i = 0; i < PROP_MAX_NODES; i++)
        prop->nodes[i] = NULL;
    prop->nodesCount = 0;

    // Setting collision
    prop->hasCollision = hasCollision;

    active_props++;

    // Setting min and max vectors in bbox
    newVec3(prop->bbox.max, pos[0] + x, pos[1] + y, pos[2] + z);
    newVec3(prop->bbox.min, pos[0] - x, pos[1] - y, pos[2] - z);

    // Setting model matrix
    glm_mat4_identity(prop->model);
    glm_translate(prop->model, prop->pos);
    
    // Setting VBO and VAO
    glGenVertexArrays(1, &prop->VAO);
    glBindVertexArray(prop->VAO);
    glGenBuffers(1, &prop->VBO);
    glBindBuffer(GL_ARRAY_BUFFER, prop->VBO);
    glBufferData(GL_ARRAY_BUFFER, PROP_MAX_VERTICES * sizeof(vec3), prop->vertices, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (void *)0);
    glEnableVertexAttribArray(0);

    // Unbinding
    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

// Null the prop array
void initPropArray() {
    for (int i = 0; i < MAX_PROPS; i++)
        props[i] = NULL;
}

// Freeing memory for prop
void killProp(Prop* prop) {
    for (int i = 0; i < MAX_PROPS; i++) {
        if (props[i] == prop) {
            free(prop->nodes);
            props[i] = NULL;    
            active_props--;

            i++;

            while (i < MAX_PROPS && props[i] != NULL) {
                props[i - 1] = props[i];
                i++;
            }

            return;
        }
    }
}
