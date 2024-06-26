// Variables to keep track of time between frames 
GLfloat deltaTime = 0.0f;
GLfloat lastFrame = 0.0f;
GLfloat currentFrame;

// Is app running
bool isPaused = false;

updateDeltaTime();

// Updates delta time to make stuff not fps-related
updateDeltaTime()
{
    currentFrame = glfwGetTime();
    deltaTime = currentFrame - lastFrame;
    lastFrame = currentFrame;
}