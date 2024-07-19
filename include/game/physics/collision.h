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

#define NODE_MAX_PROPS 1
#define NODE_MAX_DEPTH 64

// Octree struct implemented to optimize collision
typedef struct OctreeNode {
  Prop **props;
  int activeProps;
  int depth;
  Bbox nodeRegion;
  struct OctreeNode* children[8];
  bool isLeaf;
} OctreeNode;

extern OctreeNode* root;
extern bool octreeCreated;
extern bool dbgRenderOctree;

bool playerCollisionDetect(vec3 newPos);
bool AABBcollision(Bbox a, Bbox b);
OctreeNode* octreeCreate(float xMin, float yMin, float zMin, float xMax, float yMax, float zMax);
void octreeSubdivide(OctreeNode* node);
void octreeInsertProp(Prop* prop, OctreeNode* node);
void octreeDraw(OctreeNode* node);
void octreeKill(OctreeNode* node);
void octreeUpdate(OctreeNode* node);