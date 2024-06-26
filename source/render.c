// Custom modules
#include <render.h>
#include <window.h>

// Is app paused. Initially set to false.
bool isPaused = false;

// Is app running. Intially set to true.
bool isRunning = true;

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