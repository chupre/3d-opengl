// Standatd includes
#include <string.h>

// Custom modules
#include <player.h>

Player player;

void initPlayer()
{
    player.height = 1.0f;
    
    vec3 leftDownVertex = { -0.5f, 0.0f, -0.5f };
    vec3 rightDownVertex = { 0.5f, 0.0f, 0.5f };
    vec3 leftUpVertex = { -0.5f, 1.0f, -0.5f };
    vec3 rightUpVertex = { 0.5f, 1.0f, 0.5f };
    memcpy(player.bbox[0], leftDownVertex, sizeof(vec3));
    memcpy(player.bbox[1], rightDownVertex, sizeof(vec3));
    memcpy(player.bbox[2], leftUpVertex, sizeof(vec3));
    memcpy(player.bbox[3], rightUpVertex, sizeof(vec3));

    // Set in world center
    player.position[0] = 0.0f;
    player.position[1] = player.height;
    player.position[2] = 0.0f; 

    // Set states to default
    player.states.noclip = false;
}