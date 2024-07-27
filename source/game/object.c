// Custom modules
#include <object.h>
#include <camera.h>
#include <vector.h>

Object* objects[MAX_OBJECTS];
int active_objects = 0;

// Creates object VBO and VAO and sets object's fields
void newObject(Object* object, vec3 pos, vec3 offset, bool hasCollision, float textureTilingMultiplier) {
    bool objectCreated = false;

    // Setting pointer in objects array
    for (int i = 0; i < MAX_OBJECTS; i++)
    {
        if (objects[i] == NULL)
        {
            objects[i] = object;
            objectCreated = true;
            break;
        }
    }

    // Check if there was a free space for the object
    if (!objectCreated)
        return;

    // Setting vertices in object
    GLfloat x = offset[0];
    GLfloat y = offset[1];
    GLfloat z = offset[2];

    // Define the vertices and texture coordinates
    GLfloat objectVertices[] = {
        // Positions          // Texture Coords
        // Front face
        -x, -y, -z,          0.0f, 0.0f,
         x, -y, -z,          textureTilingMultiplier, 0.0f,
         x,  y, -z,          textureTilingMultiplier, textureTilingMultiplier,
         x,  y, -z,          textureTilingMultiplier, textureTilingMultiplier,
        -x,  y, -z,          0.0f, textureTilingMultiplier,
        -x, -y, -z,          0.0f, 0.0f,

        // Back face
        -x, -y,  z,          0.0f, 0.0f,
         x, -y,  z,          textureTilingMultiplier, 0.0f,
         x,  y,  z,          textureTilingMultiplier, textureTilingMultiplier,
         x,  y,  z,          textureTilingMultiplier, textureTilingMultiplier,
        -x,  y,  z,          0.0f, textureTilingMultiplier,
        -x, -y,  z,          0.0f, 0.0f,

        // Left face
        -x,  y,  z,          0.0f, 0.0f,
        -x,  y, -z,          textureTilingMultiplier, 0.0f,
        -x, -y, -z,          textureTilingMultiplier, textureTilingMultiplier,
        -x, -y, -z,          textureTilingMultiplier, textureTilingMultiplier,
        -x, -y,  z,          0.0f, textureTilingMultiplier,
        -x,  y,  z,          0.0f, 0.0f,

        // Right face
        x,  y, -z,           textureTilingMultiplier, 0.0f,
        x,  y,  z,           0.0f, 0.0f,
        x, -y, -z,           textureTilingMultiplier, textureTilingMultiplier,
        x, -y, -z,           textureTilingMultiplier, textureTilingMultiplier,
        x, -y,  z,           0.0f, textureTilingMultiplier,
        x,  y,  z,           0.0f, 0.0f,

        // Bottom face
        -x, -y, -z,          0.0f, 0.0f,
         x, -y, -z,          textureTilingMultiplier, 0.0f,
         x, -y,  z,          textureTilingMultiplier, textureTilingMultiplier,
         x, -y,  z,          textureTilingMultiplier, textureTilingMultiplier,
        -x, -y,  z,          0.0f, textureTilingMultiplier,
        -x, -y, -z,          0.0f, 0.0f,

        // Top face
        -x,  y, -z,          0.0f, 0.0f,
         x,  y, -z,          textureTilingMultiplier, 0.0f,
         x,  y,  z,          textureTilingMultiplier, textureTilingMultiplier,
         x,  y,  z,          textureTilingMultiplier, textureTilingMultiplier,
        -x,  y,  z,          0.0f, textureTilingMultiplier,
        -x,  y, -z,          0.0f, 0.0f,
    };
    
    memcpy(object->vertices, objectVertices, sizeof(objectVertices));
    memcpy(object->offset, offset, sizeof(vec3));
    memcpy(object->pos, pos, sizeof(vec3));

    for (int i = 0; i < OBJECT_MAX_NODES; i++)
        object->nodes[i] = NULL;

    object->nodesCount = 0;

    // Setting collision
    object->hasCollision = hasCollision;

    active_objects++;

    // Setting min and max vectors in bbox
    newVec3(object->bbox.max, pos[0] + x, pos[1] + y, pos[2] + z);
    newVec3(object->bbox.min, pos[0] - x, pos[1] - y, pos[2] - z);

    // Setting model matrix
    glm_mat4_identity(object->model);
    glm_translate(object->model, object->pos);

    // Setting default texture
    setObjectTexture(object, "default.png");
    
    // Setting VBO and VAO
    glGenVertexArrays(1, &object->VAO);
    glBindVertexArray(object->VAO);
    glGenBuffers(1, &object->VBO);
    glBindBuffer(GL_ARRAY_BUFFER, object->VBO);
    glBufferData(GL_ARRAY_BUFFER, OBJECT_MAX_VERTICES * sizeof(vec3), object->vertices, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (void *)0);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (void *)(3 * sizeof(GLfloat)));
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);  

    // Unbinding
    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

// Null the object array
void initObjectArray() {
    for (int i = 0; i < MAX_OBJECTS; i++)
        objects[i] = NULL;
}

// Freeing memory for object
void killObject(Object* object) {
    for (int i = 0; i < MAX_OBJECTS; i++) {
        if (objects[i] == object) {
            // free(object->nodes);
            objects[i] = NULL;    
            active_objects--;

            i++;

            while (i < MAX_OBJECTS && objects[i] != NULL) {
                objects[i - 1] = objects[i];
                i++;
            }

            return;
        }
    }
}

void setObjectTexture(Object* object, unsigned char* texture_name) {
    for (int i = 0; i < textures_count; i++)
        if (strcmp(textures[i].name, texture_name) == 0)
            object->texture = textures[i];        
}
