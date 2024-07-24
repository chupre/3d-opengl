#include <octree.h>
#include <collision.h>
#include <vector.h>
#include <prop.h>
#include <player.h>
#include <update.h>
#include <camera.h>

OctreeNode *root;
bool octreeCreated = false;
bool dbgRenderOctree = false;

// Returns a new octree node
OctreeNode *octreeCreate(float xMin, float yMin, float zMin, 
                         float xMax, float yMax, float zMax) {
  // Initializing the node
  OctreeNode *node = (OctreeNode *)malloc(sizeof(OctreeNode));
  newVec3(node->nodeRegion.min, xMin, yMin, zMin);
  newVec3(node->nodeRegion.max, xMax, yMax, zMax);
  node->propsCount = 0;
  node->isLeaf = true;
  node->props = NULL;
  node->depth = 0;
  for (int i = 0; i < 8; i++)
    node->children[i] = NULL;

  if (!octreeCreated) {
    octreeCreated = true;
    octreeSubdivide(node);
  }

  return node;
}

// Subdivides the node in 8 octants
void octreeSubdivide(OctreeNode *node) {
  // Setting vector for center of node cube
  vec3 nodeCenter = {(node->nodeRegion.max[0] + node->nodeRegion.min[0]) / 2.0f,
                     (node->nodeRegion.max[1] + node->nodeRegion.min[1]) / 2.0f,
                     (node->nodeRegion.max[2] + node->nodeRegion.min[2]) / 2.0f};

  int nodeSize = node->nodeRegion.max[0] - nodeCenter[0];

  node->children[TopLeftFront] = octreeCreate(
      nodeCenter[0] - nodeSize, nodeCenter[1], nodeCenter[2] - nodeSize,
      nodeCenter[0], nodeCenter[1] + nodeSize, nodeCenter[2]);

  node->children[TopRightFront] = octreeCreate(
      nodeCenter[0], nodeCenter[1], nodeCenter[2] - nodeSize,
      nodeCenter[0] + nodeSize, nodeCenter[1] + nodeSize, nodeCenter[2]);

  node->children[BottomRightFront] = octreeCreate(
      nodeCenter[0], nodeCenter[1] - nodeSize, nodeCenter[2] - nodeSize,
      nodeCenter[0] + nodeSize, nodeCenter[1], nodeCenter[2]);

  node->children[BottomLeftFront] = octreeCreate(
      nodeCenter[0] - nodeSize, nodeCenter[1] - nodeSize,
      nodeCenter[2] - nodeSize, nodeCenter[0], nodeCenter[1], nodeCenter[2]);

  node->children[TopLeftBack] = octreeCreate(
      nodeCenter[0] - nodeSize, nodeCenter[1], nodeCenter[2], nodeCenter[0],
      nodeCenter[1] + nodeSize, nodeCenter[2] + nodeSize);

  node->children[TopRightBack] = octreeCreate(
      nodeCenter[0], nodeCenter[1], nodeCenter[2], nodeCenter[0] + nodeSize,
      nodeCenter[1] + nodeSize, nodeCenter[2] + nodeSize);

  node->children[BottomRightBack] = octreeCreate(
      nodeCenter[0], nodeCenter[1] - nodeSize, nodeCenter[2],
      nodeCenter[0] + nodeSize, nodeCenter[1], nodeCenter[2] + nodeSize);

  node->children[BottomLeftBack] = octreeCreate(
      nodeCenter[0] - nodeSize, nodeCenter[1] - nodeSize, nodeCenter[2],
      nodeCenter[0], nodeCenter[1], nodeCenter[2] + nodeSize);

  node->isLeaf = false;
  for (int i = 0; i < 8; i++)
    node->children[i]->depth = node->depth + 1;
}

// Recursively inserts a prop in node by dividing the octree
void octreeInsertProp(Prop *prop, OctreeNode *node) {
  for (int i = 0; i < 8; i++) {
    if (node->children[i] != NULL && AABBcollision(node->children[i]->nodeRegion, prop->bbox)) {
      if (!node->children[i]->isLeaf) {
        octreeInsertProp(prop, node->children[i]);
      } else if (node->children[i]->propsCount < NODE_MAX_PROPS || node->children[i]->depth == NODE_MAX_DEPTH) {
        if (prop->nodesCount < PROP_MAX_NODES) {
          prop->nodesCount++;
          prop->nodes[prop->nodesCount - 1] = node->children[i];
        }

        node->children[i]->propsCount++;
        node->children[i]->props = realloc(node->children[i]->props, node->children[i]->propsCount * sizeof(Prop *));
        node->children[i]->props[node->children[i]->propsCount - 1] = prop;
      } else {
        octreeSubdivide(node->children[i]); 
        for (int j = 0; j < node->children[i]->propsCount; j++)
          octreeInsertProp(node->children[i]->props[j], node->children[i]);
        octreeInsertProp(prop, node->children[i]);
        node->children[i]->props = NULL;
        node->children[i]->propsCount = 0;
      }
    }
  }
}

// Recursively draws the border lines of an octree. Not optimal
void octreeDraw(OctreeNode *node) {
  vec3 nodeCenter = {(node->nodeRegion.max[0] + node->nodeRegion.min[0]) / 2.0f,
                     (node->nodeRegion.max[1] + node->nodeRegion.min[1]) / 2.0f,
                     (node->nodeRegion.max[2] + node->nodeRegion.min[2]) / 2.0f};

  int nodeSize = node->nodeRegion.max[0] - nodeCenter[0];

  // Setting vertices for octree border lines
  float nodeVertices[] = {
      // Frontside top line
      nodeCenter[0] - nodeSize,
      nodeCenter[1] + nodeSize,
      nodeCenter[2] - nodeSize,
      nodeCenter[0] + nodeSize,
      nodeCenter[1] + nodeSize,
      nodeCenter[2] - nodeSize,

      // Frontside bottom line
      nodeCenter[0] - nodeSize,
      nodeCenter[1] - nodeSize,
      nodeCenter[2] - nodeSize,
      nodeCenter[0] + nodeSize,
      nodeCenter[1] - nodeSize,
      nodeCenter[2] - nodeSize,

      // Frontside left line
      nodeCenter[0] - nodeSize,
      nodeCenter[1] + nodeSize,
      nodeCenter[2] - nodeSize,
      nodeCenter[0] - nodeSize,
      nodeCenter[1] - nodeSize,
      nodeCenter[2] - nodeSize,

      // Frontside right line
      nodeCenter[0] + nodeSize,
      nodeCenter[1] + nodeSize,
      nodeCenter[2] - nodeSize,
      nodeCenter[0] + nodeSize,
      nodeCenter[1] - nodeSize,
      nodeCenter[2] - nodeSize,

      // Backside top line
      nodeCenter[0] - nodeSize,
      nodeCenter[1] + nodeSize,
      nodeCenter[2] + nodeSize,
      nodeCenter[0] + nodeSize,
      nodeCenter[1] + nodeSize,
      nodeCenter[2] + nodeSize,

      // Backside bottom line
      nodeCenter[0] - nodeSize,
      nodeCenter[1] - nodeSize,
      nodeCenter[2] + nodeSize,
      nodeCenter[0] + nodeSize,
      nodeCenter[1] - nodeSize,
      nodeCenter[2] + nodeSize,

      // Backside left line
      nodeCenter[0] - nodeSize,
      nodeCenter[1] + nodeSize,
      nodeCenter[2] + nodeSize,
      nodeCenter[0] - nodeSize,
      nodeCenter[1] - nodeSize,
      nodeCenter[2] + nodeSize,

      // Backside right line
      nodeCenter[0] + nodeSize,
      nodeCenter[1] + nodeSize,
      nodeCenter[2] + nodeSize,
      nodeCenter[0] + nodeSize,
      nodeCenter[1] - nodeSize,
      nodeCenter[2] + nodeSize,

      // Rightside top line
      nodeCenter[0] + nodeSize,
      nodeCenter[1] + nodeSize,
      nodeCenter[2] - nodeSize,
      nodeCenter[0] + nodeSize,
      nodeCenter[1] + nodeSize,
      nodeCenter[2] + nodeSize,

      // Rightside bottom line
      nodeCenter[0] + nodeSize,
      nodeCenter[1] - nodeSize,
      nodeCenter[2] - nodeSize,
      nodeCenter[0] + nodeSize,
      nodeCenter[1] - nodeSize,
      nodeCenter[2] + nodeSize,

      // Leftside top line
      nodeCenter[0] - nodeSize,
      nodeCenter[1] + nodeSize,
      nodeCenter[2] - nodeSize,
      nodeCenter[0] - nodeSize,
      nodeCenter[1] + nodeSize,
      nodeCenter[2] + nodeSize,

      // Leftside bottom line
      nodeCenter[0] - nodeSize,
      nodeCenter[1] - nodeSize,
      nodeCenter[2] - nodeSize,
      nodeCenter[0] - nodeSize,
      nodeCenter[1] - nodeSize,
      nodeCenter[2] + nodeSize,
  };

  // Setting VBO and VAO
  unsigned int nodeVAO, nodeVBO;
  glGenVertexArrays(1, &nodeVAO);
  glBindVertexArray(nodeVAO);
  glGenBuffers(1, &nodeVBO);
  glBindBuffer(GL_ARRAY_BUFFER, nodeVBO);
  glBufferData(GL_ARRAY_BUFFER, sizeof(nodeVertices), nodeVertices, GL_STATIC_DRAW);
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (void *)0);
  glEnableVertexAttribArray(0);

  // Setting identity model matrix
  mat4 model;
  glm_mat4_identity(model);
  setModelUniform(model);

  // Render the node
  glBindVertexArray(nodeVAO);
  glDrawArrays(GL_LINES, 0, 36);

  // Unbinding
  glBindVertexArray(0);
  glBindBuffer(GL_ARRAY_BUFFER, 0);

  // Draw child nodes recursively
  for (int i = 0; i < 8; i++)
    if (node->children[i] != NULL)
      octreeDraw(node->children[i]);
}

// Recursively kills the whole tree
void octreeKill(OctreeNode* node) {
  if (node != NULL) {
    if (node->propsCount > 0) {
      for (int i = 0; i < node->propsCount; i++) {
        for (int j = 0; j < node->props[i]->nodesCount; j++)
          node->props[i]->nodes[j] = NULL;

        node->props[i]->nodesCount = 0;
      }
      
      free(node->props);
    }

    if (!node->isLeaf)
      for(int i = 0; i < 8; i++)
        octreeKill(node->children[i]);

    free(node);
  }

  octreeCreated = false;
}

// Rebuilds the octree recursively each update tick
// Note: can be optimized heavily
void octreeUpdate(OctreeNode *node) {
  // Clearing previous tree
  if (octreeCreated) {
    octreeKill(root);
  }

  // Octree initialization
  root = octreeCreate(-worldSize, -worldSize, -worldSize, worldSize, worldSize, worldSize);

  // Inserting all props in octree
  for (int i = 0; i < active_props; i++) 
    octreeInsertProp(props[i], root);
  
  // Updating player prop to insert it in octree
  octreeInsertProp(&playerProp, root);
}