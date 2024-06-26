// Custom modules
#include <camera.h>
#include <player.h>
#include <update.h>

// Stores information about which sides camera must move each updateCameraPosition call.
// Indices are { FORWARD, BACKWARDS, RIGHT, LEFT }.
bool cameraMovement[4];

// Variables to keep track of time between frames 
GLfloat deltaTime = 0.0f;
GLfloat lastFrame = 0.0f;
GLfloat currentFrame;

// Updates camera position each frame
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

    // Applies linear interpolation
    glm_vec3_lerp(camera.currPos, camera.targetPos, deltaTime * INTERPOLATION_MULTIPLIER, camera.currPos);

    // Copy camera pos to player pos
    glm_vec3_copy(camera.currPos, player.position);

    // Reset speedMultiplier to default.
    camera.speedMultiplier = 1.0f;
}

    
// Updates delta time to make stuff not fps-related
GLvoid updateGameTime()
{
    currentFrame = glfwGetTime();
    deltaTime = currentFrame - lastFrame;
    lastFrame = currentFrame;
}