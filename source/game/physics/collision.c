// Custom modules
#include <collision.h>
#include <player.h>
#include <prop.h>

OctreeNode* root;

// Checks collision for every prop, return true if there is collision
bool collisionDetect(vec3 newPos) {
    if (player.states.noclip)
        return false;

    Bbox newPlayerBbox;
    getNewPlayerBbox(newPos, &newPlayerBbox);

    for (int i = 0; i < active_props; i++) {
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

// Returns a new octree node
OctreeNode* newOctree(float xMin, float yMin, float zMin, float xMax, float yMax, float zMax) {
    // Initializing the node
    OctreeNode* node = (OctreeNode*)malloc(sizeof(OctreeNode));
    newVec3(node->nodeRegion.min, xMin, yMin, zMin);
    newVec3(node->nodeRegion.max, xMax, yMax, zMax);
    node->props = NULL;
    for (int i = 0; i < 8; i++)
        node->children[i] = NULL;

    return node;
    // than add insertion
    // than add dbgDrawOctree
    // than add kill and rebalance
    // than add traversion in octree
    // done 
}

// Recursively inserts a prop in node by dividing the octree
void insertOctreeProp(Prop* prop, OctreeNode* node) {
    for (int i = 0; i < 8; i++) {
      
    }
}

// Draws the borders of an octree
