// Standard includes
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// External includes
#include <glad/glad.h>
#include <GLFW/glfw3.h>

// Custom modules
#include <shader.h>
#include <player.h>
#include <update.h>
#include <render.h>
#include <camera.h>
#include <keyboard_input.h>
#include <window.h>
#include <prop.h>

int main(int argc, char** argv)
{
    // Creating window
    setWindow();

    // Generate shader program
    setShader();

    // Allocating memory for prop array
    initPropArray();

    // Creating plane
    int planeSize = 50.0f;
    GLfloat planeVertices[] = 
    {
        -planeSize, -planeSize, 0.0f,
        planeSize, -planeSize, 0.0f,
        -planeSize,  planeSize, 0.0f,
        planeSize, planeSize, 0.0f,
        planeSize, -planeSize, 0.0f,
        -planeSize,  planeSize, 0.0f,
    };
    newProp(planeVertices, "plane", STATIC);

    // Player initialization
    initPlayer();

    // Camera initialization
    initCamera();

    // Activate shader
    glUseProgram(shaderProgram);

    // Since projection matrix rarely changes there is no need to put it in render loop
    setProjectionUniform();

    // Main loop
    while(isRunning)
    {
        updateGameTime();
        processKeyboardInput();

        while (deltaTimeTick >= 1.0)
        {
            update();
            deltaTimeTick--;
        }

        if (!isPaused)
        {
            render();
        }

        showFPS();

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // End of program
    quit();
}
