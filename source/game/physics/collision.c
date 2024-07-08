// Custom modules
#include <collision.h>
#include <player.h>

// Checks collision for every prop, return true if there is collision
bool collisionDetect(vec3 newPos) {
    if (player.states.noclip)
        return false;

    vec3 newBbox[4];
    getNewPlayerBbox(newPos, newBbox);

    for (int i = 0; i < MAX_PROPS; i++) {
        if (props[i]  && props[i]->hasCollision && AABBcollision(newBbox, props[i]->bbox))
            return true;
    }
    
    return false;
}

// Checks axis aligned bounding boxes collision (only for objects with box-type bounding volume)
bool AABBcollision(vec3 bbox_1[4], vec3 bbox_2[4]) {
    // Getting min and max vertices of bboxes
    vec3 bbox_1_min = { bbox_1[0][0], bbox_1[0][1], bbox_1[0][2] };
    vec3 bbox_2_min = { bbox_2[0][0], bbox_2[0][1], bbox_2[0][2] };
    vec3 bbox_1_max = { bbox_1[3][0], bbox_1[3][1], bbox_1[3][2] };
    vec3 bbox_2_max = { bbox_2[3][0], bbox_2[3][1], bbox_2[3][2] };

    // Returns true if there is  collision
    return (
        bbox_1_min[0] <= bbox_2_max[0] &&
        bbox_1_max[0] >= bbox_2_min[0] &&
        bbox_1_min[1] <= bbox_2_max[1] &&
        bbox_1_max[1] >= bbox_2_min[1] &&
        bbox_1_min[2] <= bbox_2_max[2] &&
        bbox_1_max[2] >= bbox_2_min[2]     
    );

    return false;
}

