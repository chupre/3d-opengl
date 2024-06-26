// Standard includes
#include <stdbool.h>

// External
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <cglm/cglm.h>

#define TICK_COUNT 60.0
#define TICK 1.0 / TICK_COUNT
#define INTERPOLATION_MULTIPLIER 2.0f

// Stores information about which sides camera must move each updateCameraPosition call.
// Indices are { FORWARD, BACKWARDS, RIGHT, LEFT }.
extern bool cameraMovement[4];

// Variables to keep track of time between frames 
extern GLfloat deltaTime;
extern GLfloat lastFrame;
extern GLfloat currentFrame;

GLvoid updateCameraPosition();
GLvoid updateGameTime();