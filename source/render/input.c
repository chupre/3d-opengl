// Custom modules
#include <input.h>
#include <camera.h>
#include <update.h>
#include <render.h>
#include <octree.h>
#include <player.h>
#include <prop.h>
#include <window.h>

// Keymap for keys.
// Key code == key index.
// Stores true if pressed, false if not.
bool keys[NUMBER_OF_KEYS];

// This boolean uses when program starts or unpauses to prevent weird mouse movements. 
// Initially set by true.
bool firstMouseInput = true;

// Cursor position centered in middle
GLfloat lastCursorPosX = (float)WINDOW_WIDTH / 2.0f;
GLfloat lastCursorPosY = (float)WINDOW_HEIGHT / 2.0f;

// Apply user input to game logic
void processKeyboardInput()
{
    // Resets camera directions
    memset(cameraMovement, false, sizeof(cameraMovement));

    for (int i = 0; i < NUMBER_OF_KEYS; i++)
    {
        // If key is pressed
        if (keys[i])
        {
            switch(i)
            {
                // Movement
                case GLFW_KEY_W:
                    cameraMovement[FORWARD] = true;
                    break;

                case GLFW_KEY_S:
                    cameraMovement[BACKWARDS] = true;
                    break;

                case GLFW_KEY_A:
                    cameraMovement[LEFT] = true;
                    break;

                case GLFW_KEY_D:
                    cameraMovement[RIGHT] = true;
                    break;

                case GLFW_KEY_LEFT_SHIFT:
                    camera.speedMultiplier = DEFAULT_CAMERA_SPEED_MULTIPLIER;
                    break;
            }
        }
    }
}

// Callback for processing keyboard input
GLvoid keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods) {
        // Using keymap for movement
        if (action == GLFW_PRESS)
            keys[key] = true;
        else if (action == GLFW_RELEASE)
            keys[key] = false;

        // Pause
        if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
            togglePause();
        

        // Debug: draw octree
        if (key == GLFW_KEY_F3 && action == GLFW_PRESS)
            dbgRenderOctree = !dbgRenderOctree;

        // Exit game
        if (key == GLFW_KEY_F6 && action == GLFW_PRESS)
            isRunning = false;

        // Noclip
        if (key == GLFW_KEY_N && action == GLFW_PRESS) {
            player.states.noclip = !player.states.noclip;
            camera.targetPos[1] = 1.0f;
        }

        // Debug: placing cube
        if (key == GLFW_KEY_F && action == GLFW_PRESS) {
            vec3 cubeOffset = {5.0f, 5.0f, 5.0f };
            Prop* cube = malloc(sizeof(Prop));
            newProp(cube, player.position, cubeOffset, true);
        }
}

// Callback for processing mouse input
GLvoid mouseCallback(GLFWwindow* window, double xpos, double ypos) {
    if (!isPaused) {
        // Checks if the mouse input is the first one to prevent weird camera movements
        if (firstMouseInput) {
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
            pitch = 89.0f;

        if (pitch < -89.0f)
            pitch = -89.0f;

        // Applying offsets to camera position
        applyMouseInput();
    }
}

// Callback for scroll. Scrolling zooms camera in and out
GLvoid scrollCallback(GLFWwindow* window, double xoffset, double yoffset) {
    camera.FOV -= (float)yoffset * camera.speedMultiplier;

    // Max and min FOV restrictions
    if (camera.FOV < 1.0f)
        camera.FOV = 1.0f;

    if (camera.FOV > DEFAULT_FOV)
        camera.FOV = DEFAULT_FOV;

    // Recalculating projection matrix based on new FOV
    setProjectionUniform();
}