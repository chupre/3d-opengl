// Custom modules
#include <camera.h>
#include <player.h>
#include <update.h>
#include <render.h>
#include <prop.h>

// Root scene size - World size
GLfloat worldSize = 2000.0f;

// Stores information about which sides camera must move each updateCameraPosition call.
// Indices are { FORWARD, BACKWARDS, RIGHT, LEFT }.
bool cameraMovement[4];

// Variables to keep track of time between frames 
GLdouble deltaTime = 0.0f;
GLdouble lastFrame = 0.0f;
GLdouble currentFrame;

// Tick time
GLdouble tick = 1.0 / TICK_COUNT;
GLdouble deltaTimeTick = 0.0f;

// Used for fps counter
GLdouble timer = 0.0f;

// Update counter
int updates = 0;

// Updates delta time to make stuff not fps-related
GLvoid updateGameTime()
{
    currentFrame = glfwGetTime();
    deltaTime = currentFrame - lastFrame;
    deltaTimeTick += deltaTime / tick;
    lastFrame = currentFrame;
}

// Updates camera position each tick
GLvoid updateCameraPosition()
{
    // Moves camera depends on directions from user input
    if (cameraMovement[FORWARD])
    {
        moveCameraTarget(FORWARD);
    }
    if (cameraMovement[BACKWARDS])
    {
        moveCameraTarget(BACKWARDS);
    }
    if (cameraMovement[LEFT])
    {
        moveCameraTarget(LEFT);
    }
    if (cameraMovement[RIGHT])
    {
        moveCameraTarget(RIGHT);
    }

    // Copy camera pos to player pos
    glm_vec3_copy(camera.currPos, player.position);

    // Reset speedMultiplier to default.
    camera.speedMultiplier = 1.0f;
}

// Updates game state every tick
GLvoid update()
{
    updateCameraPosition();
    updates++;
}
