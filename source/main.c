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

    // Creating test objects
    vec3 planeOffset = {50.0f, 0.0f, 50.0f};
    vec3 planePos = { 0.0f, 0.0f, 0.0f };
    Prop plane;
    newProp(&plane, planePos, planeOffset, true);

    vec3 test1Offset = {2.0f, 5.0f, 2.0f };
    vec3 test1Pos = { 10.0f, 5.0f, 0.0f };
    Prop test1;
    newProp(&test1, test1Pos, test1Offset, true);

    vec3 test2Offset = {2.0f, 5.0f, 2.0f };
    vec3 test2Pos = { -10.0f, 5.0f, 0.0f };
    Prop test2;
    newProp(&test2, test2Pos, test2Offset, true);

    vec3 test3Offset = {2.0f, 5.0f, 2.0f };
    vec3 test3Pos = { 10.0f, 5.0f, 10.0f };
    Prop test3;
    newProp(&test3, test3Pos, test3Offset, true);

    vec3 test4Offset = {2.0f, 5.0f, 2.0f };
    vec3 test4Pos = { -10.0f, 5.0f, 10.0f };
    Prop test4;
    newProp(&test4, test4Pos, test4Offset, true);

    vec3 test5Offset = {12.0f, 0.0f, 7.0f };
    vec3 test5Pos = { 0.0f, 10.0f, 5.0f };
    Prop test5;
    newProp(&test5, test5Pos, test5Offset, true);

    vec3 test6Offset = {4.0f, 15.0f, 700.0f };
    vec3 test6Pos = { -60.0f, 0.0f, 5.0f };
    Prop test6;
    newProp(&test6, test6Pos, test6Offset, true);

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
