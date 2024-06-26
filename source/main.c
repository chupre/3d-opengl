// Standard includes
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// External includes
#define STB_IMAGE_IMPLEMENTATION
#include <stb/stb_image.h>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <cglm/cglm.h>

// Custom modules
#include <macros.h>
#include <render.h>
#include <shaders/shader.h>
#include <camera.h>
#include <window.h>
#include <object.h>

int main(int argc, char** argv)
{
    // Creating window
    setWindow();

    // Generate shader program
    setShader();

    // Creating plane
    object plane;
    GLfloat planeVertices[] = 
    {
        -10.0f, -10.0f, 0.0f,
        10.0f, -10.0f, 0.0f,
        -10.0f,  10.0f, 0.0f,
        10.0f, 10.0f, 0.0f,
        10.0f, -10.0f, 0.0f,
        -10.0f,  10.0f, 0.0f,
    };
    newObject(&plane, planeVertices, "plane", STATIC);

    // Activate shader
    glUseProgram(shaderProgram);

    // Since projection matrix rarely changes there is no need to put in render loop
    setProjectionUniform();

    // Main loop
    while(!glfwWindowShouldClose(window))
    {
        updateDeltaTime();

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
    glDeleteProgram(shaderProgram);
    glfwTerminate();
    return EXIT_SUCCESS;
}
