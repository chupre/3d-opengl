// Standard include
#include <stdbool.h>

// External include
#include <glad/glad.h>
#include <cglm/cglm.h>

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

extern Player player;

void initPlayer();