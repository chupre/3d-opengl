// Standatd includes
#include <string.h>

// Custom modules
#include <player.h>

Player player;

void initPlayer() {
    player.height = 1.0f;
    player.width = 1.0f;
    player.depth = 1.0f;
    
    getNewPlayerBbox(player.position, &player.bbox);

    // Set in world center
    player.position[0] = 0.0f;
    player.position[1] = player.height;
    player.position[2] = 0.0f; 

    // Set states to default
    player.states.noclip = false;
}

// Stores in dest new player bounding box related to pos vector
void getNewPlayerBbox(vec3 pos, Bbox* b) {
    GLfloat x = pos[0];
    GLfloat y = pos[1];
    GLfloat z = pos[2];

    // Setting player bounding box for collision
    vec3 leftDownVertex = { x - player.width, y - player.height, z - player.depth };
    vec3 rightDownVertex = { x + player.width, y - player.height, z + player.depth };
    vec3 leftUpVertex = { x - player.width, y, z - player.depth };
    vec3 rightUpVertex = { x + player.width, y, z + player.depth };
    memcpy(b->corners[0], leftDownVertex, sizeof(vec3));
    memcpy(b->corners[1], rightDownVertex, sizeof(vec3));
    memcpy(b->corners[2], leftUpVertex, sizeof(vec3));
    memcpy(b->corners[3], rightUpVertex, sizeof(vec3));

    // Setting min and max vectors
    memcpy(b->max, b->corners[3], sizeof(vec3));
    memcpy(b->min, b->corners[0], sizeof(vec3));
}
