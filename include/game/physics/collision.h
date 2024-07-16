// Standard includes
#include <stdbool.h>

// External
#include <cglm/cglm.h>

// Custom modules
#include <bbox.h>
#include <prop.h>
#include <vector.h>

// Octree octants
#define TopLeftFront 0
#define TopRightFront 1
#define BottomRightFront 2
#define BottomLeftFront 3
#define TopLeftBack 4
#define TopRightBack 5
#define BottomRightBack 6
#define BottomLeftBack 7

// Octree struct implemented to optimize collision
typedef struct OctreeNode {
  Prop **props;
  Bbox nodeRegion;
  struct OctreeNode* children[8];
} OctreeNode;

extern OctreeNode* root;

bool collisionDetect(vec3 newPos);
bool AABBcollision(Bbox a, Bbox b);
OctreeNode* newOctree(float xMin, float yMin, float zMin, float xMax, float yMax, float zMax);
void insertOctreeProp(Prop* prop, OctreeNode* node);