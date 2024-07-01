// Custom modules
#include <player.h>

Player player;

void initPlayer()
{
    player.height = 1.0f;
    
    // Set in world center
    player.position[0] = 0.0f;
    player.position[1] = player.height;
    player.position[2] = 0.0f; 

    // Set states to default
    player.states.noclip = true;
}