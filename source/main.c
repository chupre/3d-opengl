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

    initPropArray();

    // Creating plane
    vec3 planeOffset = {50.0f, 50.0f, 0.0f};
    vec3 planePos = { 0.0f, 0.0f, 0.0f };
    Prop plane;
    newProp(&plane, planePos, planeOffset, true);

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
