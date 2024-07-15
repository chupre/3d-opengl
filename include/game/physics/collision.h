// Standard includes
#include <stdbool.h>

// External
#include <cglm/cglm.h>

// Custom modules
#include <bbox.h>
#include <prop.h>

#define OCT_NODE_MIN_SIZE 0.5f

// Octree struct implemented to optimize collision
typedef struct OctreeNode {
  Prop **props;
  Bbox nodeRegion;
  struct OctreeNode *children[8];
} OctreeNode;

extern OctreeNode root;

bool collisionDetect(vec3 newPos);
bool AABBcollision(Bbox a, Bbox b);
OctreeNode newOctree(float xMin, float yMin, float zMin, float xMax, float yMax, float zMax);
void insertOctreeProp(Prop* prop, OctreeNode* node);