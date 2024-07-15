// Standard includes
#include <stdbool.h>

// External
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <cglm/cglm.h>

#define TICK_COUNT 60.0
#define INTERPOLATION_MULTIPLIER 5.0f

// Stores information about which sides camera must move each updateCameraPosition call.
// Indices are { FORWARD, BACKWARDS, RIGHT, LEFT }.
extern bool cameraMovement[4];

// Update counter
extern int updates;

// Root scene size - World size
extern GLfloat worldSize;

// Variables to keep track of time between frames 
extern GLdouble deltaTime;
extern GLdouble lastFrame;
extern GLdouble currentFrame;

// Tick time
extern GLdouble tick;
extern GLdouble deltaTimeTick;

// Used for fps counter
extern GLdouble timer;

GLvoid updateGameTime();
GLvoid updateCameraPosition();
GLvoid update();
GLvoid showFPS();
