// External includes
#include <glad/glad.h>
#include <GLFW/glfw3.h>

// Custom modules
#include <shader.h>
#include <player.h>
#include <update.h>
#include <render.h>
#include <camera.h>
#include <input.h>
#include <window.h>
#include <object.h>
#include <collision.h>
#include <texture.h>

int main(int argc, char** argv) {
    // Creating window
    setWindow();

    // Generate shader program
    setShader();

    // Preinitializing object pointers array
    initObjectArray();

    // Sets up OpenGL and loads textures
    initTextures();
    
    vec3 planeOffset = {50.0f, 0.0f, 50.0f};
    vec3 planePos = { 0.0f, 0.0f, 0.0f };
    Object plane;
    newObject(&plane, planePos, planeOffset, true);

    vec3 test1Offset = {2.0f, 5.0f, 2.0f };
    vec3 test1Pos = { 10.0f, 5.0f, 0.0f };
    Object test1;
    newObject(&test1, test1Pos, test1Offset, true);

    vec3 test2Offset = {2.0f, 5.0f, 2.0f };
    vec3 test2Pos = { -10.0f, 5.0f, 0.0f };
    Object test2;
    newObject(&test2, test2Pos, test2Offset, true);
    
    vec3 test3Offset = {2.0f, 5.0f, 2.0f };
    vec3 test3Pos = { 10.0f, 5.0f, 10.0f };
    Object test3;
    newObject(&test3, test3Pos, test3Offset, true);
    
    vec3 test4Offset = {2.0f, 5.0f, 2.0f };
    vec3 test4Pos = { -10.0f, 5.0f, 10.0f };
    Object test4;
    newObject(&test4, test4Pos, test4Offset, true);
    
    vec3 test5Offset = {12.0f, 0.0f, 7.0f };
    vec3 test5Pos = { 0.0f, 10.0f, 5.0f };
    Object test5;
    newObject(&test5, test5Pos, test5Offset, true);

    octreeUpdate(root);

    // Player initialization
    initPlayer();

    // Camera initialization
    initCamera();

    // Activate shader
    glUseProgram(shaderProgram);

    // Since projection matrix rarely changes there is no need to put it in render loop
    setProjectionUniform();

    // Main loop
    while(isRunning) {
        updateGameTime();
        processKeyboardInput();

        if (!isPaused) {
            while (deltaTimeTick >= 1.0) {
                update();
                deltaTimeTick--;
            }
        }

        render();

        showFPS();

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // End of program
    quit();
}
