// Standard includes
#include <stdio.h>

// Custom modules
#include <render.h>
#include <window.h>
#include <prop.h>
#include <camera.h>
#include <update.h>
#include <player.h>

// Is app paused. Initially set to false.
bool isPaused = false;

// Is app running. Intially set to true.
bool isRunning = true;

int frames = 0;

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

// Main render function
GLvoid render()
{
    glClearColor(0.529f, 0.808f, 0.922f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    setModelUniform();
    setViewUniform();

    // Apply linear interpolation to camera movement
    glm_vec3_lerp(camera.currPos, camera.targetPos, deltaTime * INTERPOLATION_MULTIPLIER, camera.currPos);
    
    // Rendering evry prop
    for (int i = 0; i < propCount; i++)
    {
        glBindVertexArray(props[i].VAO);
        glDrawArrays(GL_TRIANGLES, 0, 6);
    }

    frames++;
}

// Prints FPS every second
void showFPS()
{
    if (glfwGetTime() - timer > 1)
    {
        printf("FPS: %d, Updates: %d\n", frames, updates);
        timer += 1;
        frames = 0;
        updates = 0;
    }
}