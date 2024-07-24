#pragma once

// Standard includes
#include <stdbool.h>

// Custom modules
#include <bbox.h>

// Octree octants
#define TopLeftFront 0
#define TopRightFront 1
#define BottomRightFront 2
#define BottomLeftFront 3
#define TopLeftBack 4
#define TopRightBack 5
#define BottomRightBack 6
#define BottomLeftBack 7

#define NODE_MAX_PROPS 4
#define NODE_MAX_DEPTH 64

typedef struct Prop Prop;
typedef struct OctreeNode OctreeNode;

// Octree struct implemented to optimize collision
struct OctreeNode {
  Prop **props;
  int propsCount;
  int depth;
  Bbox nodeRegion;
  OctreeNode* children[8];
  bool isLeaf;
};

extern OctreeNode* root;
extern bool octreeCreated;
extern bool dbgRenderOctree;

OctreeNode* octreeCreate(float xMin, float yMin, float zMin, float xMax, float yMax, float zMax);
void octreeSubdivide(OctreeNode* node);
void octreeInsertProp(Prop* prop, OctreeNode* node);
void octreeDraw(OctreeNode* node);
void octreeKill(OctreeNode *node);
void octreeUpdate(OctreeNode *node);