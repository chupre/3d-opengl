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
    vec3 planeOffset = {50.0f, 30.0f, 10.0f};
    vec3 planePos = { 0.0f, -30.0f, 0.0f };
    Prop plane;
    newProp(&plane, planePos, planeOffset, true);

    vec3 testOffset = {10.0f, 10.0f, 10.0f };
    vec3 testPos = { 10.0f, 100.0f, 10.0f };
    Prop test;
    newProp(&test, testPos, testOffset, true);

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

        // create player bounding box in player struct (remove height)
        // create avl tree for props (figure out how to sort it tho) https://stackoverflow.com/questions/1960560/how-does-3d-collision-object-detection-work
        // add collision based on https://chriscourses.com/blog/how-to-code-3d-collision-detection

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
