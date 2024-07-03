// External includes
#include <glad/glad.h>
#include <cglm/cglm.h>

#define DEFAULT_FOV 60.0f
#define DEFAULT_CAMERA_SPEED 0.5f
#define RENDER_DISTANCE 2000.0f

// Movement directions
enum direction { FORWARD, BACKWARDS, RIGHT, LEFT };

// Camera struct
typedef struct 
{
    // Camera speed multiplier, initially set to 1.0, increases when shift is pressed
    GLfloat speedMultiplier;

    GLfloat FOV;

    // Vectors for constructing view matrix
    vec3 currPos;
    vec3 front;
    vec3 up;

    // Vector for interpolating
    vec3 targetPos;
} Camera;

// Camera offset by mouse input
extern GLfloat pitch;
extern GLfloat yaw;

// Consts for transformations around x, y, z 
extern vec3 X_AXIS;
extern vec3 Y_AXIS;
extern vec3 Z_AXIS;

// Camera declaration
extern Camera camera;

void initCamera();
void setModelUniform();
void setViewUniform();
void setProjectionUniform();
void moveCameraTarget(enum direction dir);
void applyMouseInput();
