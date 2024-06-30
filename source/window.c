// Must be defined in .c file
#define STB_IMAGE_IMPLEMENTATION

// Custom modules
#include <window.h>
#include <keyboard_input.h>
#include <player.h>
#include <camera.h>
#include <shader.h>
#include <render.h>
#include <prop.h>

// Window preinitialization
GLchar* window_name = "3D-OpenGL";
GLFWwindow* window;

// Cursor position centered in middle
GLfloat lastCursorPosX = (float)WINDOW_WIDTH / 2.0f;
GLfloat lastCursorPosY = (float)WINDOW_HEIGHT / 2.0f;

GLint screenWidth = WINDOW_WIDTH;
GLint screenHeight = WINDOW_HEIGHT;

// This boolean uses when program starts or unpauses to prevent weird mouse movements. 
// Initially set by true.
bool firstMouseInput = true;

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
    images[0].pixels = pixels; glfwSetWindowIcon(window, 1, images);

    // Setting input callbacks
    glfwSetKeyCallback(window, keyCallback);
    glfwSetCursorPosCallback(window, mouseCallback);
    glfwSetScrollCallback(window, scrollCallback);

    // Keeps cursor in center of the window in order to use mouse for camera input
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    // Initialize keymap
    memset(keys, false, sizeof(keys));
}  

// Callback for processing keyboard input
GLvoid keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
        // Using keymap for movement
        if (action == GLFW_PRESS)
        {
            keys[key] = true;
        }
        else if (action == GLFW_RELEASE)
        {
            keys[key] = false;
        }

        // Pause
        if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        {
            togglePause();
        }

        // Exit game
        if (key == GLFW_KEY_F6 && action == GLFW_PRESS)
        {
            isRunning = false;
        }

        // Noclip
        if (key == GLFW_KEY_N && action == GLFW_PRESS)
        {
            player.states.noclip = !player.states.noclip;
        }
}

// Callback for processing mouse input
GLvoid mouseCallback(GLFWwindow* window, double xpos, double ypos)
{
    if (!isPaused)
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
        const float sensitivity = 0.07f;
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
}

// Callback for scroll. Scrolling zooms camera in and out
GLvoid scrollCallback(GLFWwindow* window, double xoffset, double yoffset)
{
    camera.FOV -= (float)yoffset * camera.speedMultiplier;

    // Max and min FOV restrictions
    if (camera.FOV < 1.0f)
    {
        camera.FOV = 1.0f;

    }
    if (camera.FOV > DEFAULT_FOV)
    {
        camera.FOV = DEFAULT_FOV;
    }

    // Recalculating projection matrix based on new FOV
    setProjectionUniform();
}


// Close program
GLvoid quit()
{
    glDeleteProgram(shaderProgram);
    glfwTerminate();
    free(props);
    exit(EXIT_SUCCESS);
}