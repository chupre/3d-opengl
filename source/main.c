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

    GLfloat h = 5.0f;
    GLfloat plane2Vertices[] = 
    {
        -planeSize, -planeSize + h, 0.0 +h,
        planeSize, -planeSize + h, 0.0f + h,
        -planeSize,  planeSize + h, 0.0f + h,
        planeSize, planeSize + h, 0.0f + h,
        planeSize, -planeSize + h, 0.0f + h,
        -planeSize,  planeSize + h, 0.0f + h,
    };
    newProp(plane2Vertices, "plane2", STATIC);

    // Player initialization
    initPlayer();

    // Camera initialization
    initCamera();

    // Activate shader
    glUseProgram(shaderProgram);

    // Since projection matrix rarely changes there is no need to put in render loop
    setProjectionUniform();

    // Main loop
    while(isRunning)
    {
        updateGameTime();

        updateCameraPosition();

        processKeyboardInput();

        if (!isPaused)
        {
            glClearColor(0.529f, 0.808f, 0.922f, 1.0f);
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

            setModelUniform();
            setViewUniform();
            
            for (int i = 0; i < propCount; i++)
            {
                glBindVertexArray(props[i].VAO);
                glDrawArrays(GL_TRIANGLES, 0, 6);
            }
        }

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // End of program
    quit();
}
