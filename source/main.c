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

    // Creating plane
    Prop plane;
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
    newProp(&plane, planeVertices, "plane", STATIC);

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
            
            glBindVertexArray(plane.VAO);
            glDrawArrays(GL_TRIANGLES, 0, 6);
        }

        glfwSwapBuffers(window);
        glfwPollEvents();

    }

    // End of program
    quit();
}
