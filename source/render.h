// Window preinitialization
GLchar* window_name = "3D-OpenGL";
GLFWwindow* window;

// Window size
#define WINDOW_WIDTH 1280
#define WINDOW_HEIGHT 960
GLint screenWidth = WINDOW_WIDTH;
GLint screenHeight = WINDOW_HEIGHT;
GLvoid updateDeltaTime();
GLvoid togglePause();

// Is app paused. Initially set to false.
bool isPaused = false;

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

Camera camera;

// Variables to keep track of time between frames 
GLfloat deltaTime = 0.0f;
GLfloat lastFrame = 0.0f;
GLfloat currentFrame;

GLvoid updateCameraPosition();
GLvoid updateDeltaTime();
GLvoid togglePause();

// Updates camera position each frame for linear interpolation
GLvoid updateCameraPosition()
{
    glm_vec3_lerp(camera.currPos, camera.targetPos, deltaTime * 3.0f, camera.currPos);
}


// Updates delta time to make stuff not fps-related
GLvoid updateDeltaTime()
{
    currentFrame = glfwGetTime();
    deltaTime = currentFrame - lastFrame;
    lastFrame = currentFrame;
}

// Pauses (unpauses) the game and deattaches (attaches) the mouse cursor
GLvoid togglePause()
{
    // Unpauses and returns cursor in the middle
    if (isPaused)
    {
        isPaused = false;
        glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    }
    // Pauses and makes cursor visible and not attached to the middle of screen
    else
    {
        firstMouseInput = true; // Prevents camera following new cursor position after pause
        isPaused = true;
        glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
    }
}  
