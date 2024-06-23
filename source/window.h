// Window initialization
GLchar* window_name = "3D-OpenGL";
GLFWwindow* window;

// Cursor position centered in middle
GLfloat lastCursorPosX = (float)WINDOW_WIDTH / 2.0f;
GLfloat lastCursorPosY = (float)WINDOW_HEIGHT / 2.0f;

// This boolean uses once to prevent weird mouse movements. Initially set by true
bool firstMouseInput = true;

GLvoid setWindow();
GLvoid keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
GLvoid mouseCallback(GLFWwindow* window, double xpos, double ypos);
void scrollCallback(GLFWwindow* window, double xoffset, double yoffset);

// GLFW & GLAD initialization and creating a window
GLvoid setWindow()
{
    //GLFW intialization and window settings
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

    // Setting window
    window = glfwCreateWindow(screenWidth, screenHeight, window_name, NULL, NULL);
    glfwMakeContextCurrent(window);
    gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
    glViewport(0, 0, screenWidth, screenHeight);
    glEnable(GL_DEPTH_TEST);
    
    //Setting icon for window
    GLint iconWidth, iconHeight;
    GLint channels;
    unsigned char* pixels = stbi_load("../resources/icons/window_icon.png", &iconWidth, &iconHeight, &channels, 4);
    GLFWimage images[1];
    images[0].width = iconWidth;
    images[0].height = iconHeight;
    images[0].pixels = pixels;
    glfwSetWindowIcon(window, 1, images);

    // Setting input callbacks
    glfwSetKeyCallback(window, keyCallback);
    glfwSetCursorPosCallback(window, mouseCallback);
    glfwSetScrollCallback(window, scrollCallback);

    // Keeps cursor in center of the window in order to use mouse for camera input
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);  
}  

// Callback for processing keyboard input
GLvoid keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    // Exit program
    if (glfwGetKey(window, GLFW_KEY_F6) == GLFW_PRESS)
    {
        glfwSetWindowShouldClose(window, true);
    }

    // Movement
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
    {
        moveCamera(FORWARD);
    }

    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
    {
        moveCamera(BACK);
    }

    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
    {
        moveCamera(LEFT);
    }

    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
    {
        moveCamera(RIGHT);
    }

    // Accelerating camera
    if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
    {
        cameraSpeedMultiplier = 2.0f;
    }
    else
    {
        cameraSpeedMultiplier = 1.0f;
    }
}

// Callback for processing mouse input
GLvoid mouseCallback(GLFWwindow* window, double xpos, double ypos)
{
    // Checks if the mouse input is the first one to prevent weird camera movements
    if (firstMouseInput)
    {
        lastCursorPosX = xpos;
        lastCursorPosY = ypos;
        firstMouseInput = false;
        return;
    }

    // Calculating the offset movement between last and current frame
    float xoffset = xpos - lastCursorPosX;
    float yoffset = lastCursorPosY - ypos; // reversed since y-coordinates range from bottom to top
    lastCursorPosX = xpos;
    lastCursorPosY = ypos;

    // Appyling sensitivity
    const float sensitivity = 0.1f;
    xoffset *= sensitivity;
    yoffset *= sensitivity;

    // Applying offsets
    yaw += xoffset;
    pitch += yoffset;

    // Camera constraints
    if (pitch > 89.0f)
    {
        pitch = 89.0f;
    }

    if (pitch < -89.0f)
    {
        pitch = -89.0f;
    }

    // Applying offsets to camera position
    applyMouseInput();
}

// Callback for scroll. Scrolling zooms camera in and out
void scrollCallback(GLFWwindow* window, double xoffset, double yoffset)
{
    fov -= (float)yoffset * cameraSpeedMultiplier;

    if (fov < 1.0f)
    {
        fov = 1.0f;

    }
    if (fov > DEFAULT_FOV)
    {
        fov = DEFAULT_FOV;
    }

    setProjectionUniform();
}