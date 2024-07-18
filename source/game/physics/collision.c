// Custom modules
#include <collision.h>
#include <player.h>
#include <prop.h>
#include <camera.h>

OctreeNode* root;
bool octreeCreated = false;
bool dbgRenderOctree = false;

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
OctreeNode* octreeCreate(float xMin, float yMin, float zMin, float xMax, float yMax, float zMax) {
    // Initializing the node
    OctreeNode* node = (OctreeNode*)malloc(sizeof(OctreeNode));
    newVec3(node->nodeRegion.min, xMin, yMin, zMin);
    newVec3(node->nodeRegion.max, xMax, yMax, zMax);
    node->prop = NULL;
    node->isLeaf = true;
    for (int i = 0; i < 8; i++)
        node->children[i] = NULL;

    if (!octreeCreated) {
        octreeCreated = true;
        octreeSubdivide(node);
    }

    return node;

    // than add insertion
    // than add kill and rebalance
    // than add traversion in octree
    // done 
}

// Subdivides the node in 8 octants
void octreeSubdivide(OctreeNode* node) {
    // Setting vector for center of node cube
    vec3 nodeCenter = { (node->nodeRegion.max[0] + node->nodeRegion.min[0]) / 2.0f,
                        (node->nodeRegion.max[1] + node->nodeRegion.min[1]) / 2.0f,
                        (node->nodeRegion.max[2] + node->nodeRegion.min[2]) / 2.0f };
    
    int nodeSize = node->nodeRegion.max[0] - nodeCenter[0];

    node->children[TopLeftFront]     = octreeCreate(nodeCenter[0] - nodeSize, nodeCenter[1], nodeCenter[2] - nodeSize,
                                                    nodeCenter[0], nodeCenter[1] + nodeSize, nodeCenter[2]);

    node->children[TopRightFront]    = octreeCreate(nodeCenter[0], nodeCenter[1], nodeCenter[2] - nodeSize,
                                                    nodeCenter[0] + nodeSize, nodeCenter[1] + nodeSize, nodeCenter[2]);

    node->children[BottomRightFront] = octreeCreate(nodeCenter[0], nodeCenter[1] - nodeSize, nodeCenter[2] - nodeSize,
                                                    nodeCenter[0] + nodeSize, nodeCenter[1], nodeCenter[2]);

    node->children[BottomLeftFront]  = octreeCreate(nodeCenter[0] - nodeSize, nodeCenter[1] - nodeSize, nodeCenter[2] - nodeSize,
                                                    nodeCenter[0], nodeCenter[1], nodeCenter[2]);

    node->children[TopLeftBack]      = octreeCreate(nodeCenter[0] - nodeSize, nodeCenter[1], nodeCenter[2],
                                                    nodeCenter[0], nodeCenter[1] + nodeSize, nodeCenter[2] + nodeSize);

    node->children[TopRightBack]     = octreeCreate(nodeCenter[0], nodeCenter[1], nodeCenter[2],
                                                    nodeCenter[0] + nodeSize, nodeCenter[1] + nodeSize, nodeCenter[2] + nodeSize);

    node->children[BottomRightBack]  = octreeCreate(nodeCenter[0], nodeCenter[1] - nodeSize, nodeCenter[2],
                                                    nodeCenter[0] + nodeSize, nodeCenter[1], nodeCenter[2] + nodeSize);

    node->children[BottomLeftBack]   = octreeCreate(nodeCenter[0] - nodeSize, nodeCenter[1] - nodeSize, nodeCenter[2],
                                                    nodeCenter[0], nodeCenter[1], nodeCenter[2] + nodeSize);
}

// Recursively inserts a prop in node by dividing the octree
void octreeInsertProp(Prop* prop, OctreeNode* node) {

}

// Recursively draws the border lines of an octree
void octreeDraw(OctreeNode* node) {
    vec3 nodeCenter = { (node->nodeRegion.max[0] + node->nodeRegion.min[0]) / 2.0f,
                        (node->nodeRegion.max[1] + node->nodeRegion.min[1]) / 2.0f,
                        (node->nodeRegion.max[2] + node->nodeRegion.min[2]) / 2.0f };
    
    int nodeSize = node->nodeRegion.max[0] - nodeCenter[0];

    // Setting vertices for octree border lines
    float nodeVertices[] = {
        // Frontside top line
        nodeCenter[0] - nodeSize, nodeCenter[1] + nodeSize, nodeCenter[2] - nodeSize,
        nodeCenter[0] + nodeSize, nodeCenter[1] + nodeSize, nodeCenter[2] - nodeSize,

        // Frontside bottom line
        nodeCenter[0] - nodeSize, nodeCenter[1] - nodeSize, nodeCenter[2] - nodeSize,
        nodeCenter[0] + nodeSize, nodeCenter[1] - nodeSize, nodeCenter[2] - nodeSize,

        // Frontside left line
        nodeCenter[0] - nodeSize, nodeCenter[1] + nodeSize, nodeCenter[2] - nodeSize,
        nodeCenter[0] - nodeSize, nodeCenter[1] - nodeSize, nodeCenter[2] - nodeSize,
        
        // Frontside right line
        nodeCenter[0] + nodeSize, nodeCenter[1] + nodeSize, nodeCenter[2] - nodeSize,
        nodeCenter[0] + nodeSize, nodeCenter[1] - nodeSize, nodeCenter[2] - nodeSize,

        // Backside top line
        nodeCenter[0] - nodeSize, nodeCenter[1] + nodeSize, nodeCenter[2] + nodeSize,
        nodeCenter[0] + nodeSize, nodeCenter[1] + nodeSize, nodeCenter[2] + nodeSize,
        
        // Backside bottom line
        nodeCenter[0] - nodeSize, nodeCenter[1] - nodeSize, nodeCenter[2] + nodeSize,
        nodeCenter[0] + nodeSize, nodeCenter[1] - nodeSize, nodeCenter[2] + nodeSize,

        // Backside left line
        nodeCenter[0] - nodeSize, nodeCenter[1] + nodeSize, nodeCenter[2] + nodeSize,
        nodeCenter[0] - nodeSize, nodeCenter[1] - nodeSize, nodeCenter[2] + nodeSize,
        
        // Backside right line
        nodeCenter[0] + nodeSize, nodeCenter[1] + nodeSize, nodeCenter[2] + nodeSize,
        nodeCenter[0] + nodeSize, nodeCenter[1] - nodeSize, nodeCenter[2] + nodeSize,

        // Rightside top line
        nodeCenter[0] + nodeSize, nodeCenter[1] + nodeSize, nodeCenter[2] - nodeSize,
        nodeCenter[0] + nodeSize, nodeCenter[1] + nodeSize, nodeCenter[2] + nodeSize,
   
        // Rightside bottom line
        nodeCenter[0] + nodeSize, nodeCenter[1] - nodeSize, nodeCenter[2] - nodeSize,
        nodeCenter[0] + nodeSize, nodeCenter[1] - nodeSize, nodeCenter[2] + nodeSize,

        // Leftside top line
        nodeCenter[0] - nodeSize, nodeCenter[1] + nodeSize, nodeCenter[2] - nodeSize,
        nodeCenter[0] - nodeSize, nodeCenter[1] + nodeSize, nodeCenter[2] + nodeSize,
   
        // Leftside bottom line
        nodeCenter[0] - nodeSize, nodeCenter[1] - nodeSize, nodeCenter[2] - nodeSize,
        nodeCenter[0] - nodeSize, nodeCenter[1] - nodeSize, nodeCenter[2] + nodeSize,        
    };

    
    // Setting VBO and VAO
    int nodeVAO, nodeVBO;
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
