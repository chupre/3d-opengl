// Struct for storing all kinds of temporary states player could be in.
typedef struct
{
    bool noclip;
} playerState;

// Position is {x,y,z}-vector relative to world center.
// Height represents camera tallness.
typedef struct
{
    vec3 position;
    GLfloat height;
    playerState states;
} Player;

Player player;

void initPlayer();

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