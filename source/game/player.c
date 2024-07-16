// Standatd includes
#include <string.h>

// Custom modules
#include <player.h>
#include <vector.h>

Player player;

void initPlayer() {
    player.height = 1.0f;
    player.width = 1.0f;
    player.depth = 1.0f;
    
    getNewPlayerBbox(player.position, &player.bbox);

    // Set in world center
    newVec3(player.position, 0.0f, player.height, 0.0f);

    // Set states to default
    player.states.noclip = false;
}

// Stores in dest new player bounding box related to pos vector
void getNewPlayerBbox(vec3 pos, Bbox* b) {
    GLfloat x = pos[0];
    GLfloat y = pos[1];
    GLfloat z = pos[2];

    // Setting min and max vectors in bbox
    newVec3(b->max, x + player.width, y, z + player.depth);
    newVec3(b->min, x - player.width, y - player.height, z - player.depth);
}
