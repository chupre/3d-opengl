// Custom modules
#include <collision.h>
#include <player.h>
#include <prop.h>

OctreeNode root;

// Checks collision for every prop, return true if there is collision
bool collisionDetect(vec3 newPos) {
    if (player.states.noclip)
        return false;

    Bbox newPlayerBbox;
    getNewPlayerBbox(newPos, &newPlayerBbox);

    for (int i = 0; i < MAX_PROPS; i++) {
        if (props[i]  && props[i]->hasCollision && AABBcollision(newPlayerBbox, props[i]->bbox))
            return true;
    }
    
    return false;
}

// Checks axis aligned bounding boxes collision (only for objects with box-type bounding volume)
bool AABBcollision(Bbox a, Bbox b) {
    // Returns true if there is  collision
    return (
        a.min[0] <= b.max[0] &&
        a.max[0] >= b.min[0] &&
        a.min[1] <= b.max[1] &&
        a.max[1] >= b.min[1] &&
        a.min[2] <= b.max[2] &&
        a.max[2] >= b.min[2]     
    );

    return false;
}

