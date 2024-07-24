// Custom modules
#include <camera.h>
#include <collision.h>
#include <player.h>
#include <vector.h>
#include <update.h>
#include <octree.h>

// Checks collision for every prop, return true if there is collision
bool playerCollisionDetect(vec3 newPos) {
  if (player.states.noclip)
    return false;

  Bbox oldPlayerBbox = playerProp.bbox;
  getNewPlayerBbox(newPos, &playerProp.bbox);

  octreeUpdate(root);

  for (int i = 0; i < playerProp.nodesCount; i++)
    for (int j = 0; j < playerProp.nodes[i]->propsCount; j++) {
      if (playerProp.nodes[i]->props[j]->hasCollision &&
          &playerProp != playerProp.nodes[i]->props[j] && 
          AABBcollision(playerProp.bbox, playerProp.nodes[i]->props[j]->bbox))
        return true;
    }


  playerProp.bbox = oldPlayerBbox;
  return false;
}

// Checks axis aligned bounding boxes collision (only for objects with box-type
// bounding volume)
bool AABBcollision(Bbox a, Bbox b) {
  // Returns true if there is  collision
  return (a.min[0] <= b.max[0] && a.max[0] >= b.min[0] &&
          a.min[1] <= b.max[1] && a.max[1] >= b.min[1] &&
          a.min[2] <= b.max[2] && a.max[2] >= b.min[2]);
}

