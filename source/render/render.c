// Custom modules
#include "cglm/vec3.h"
#include <render.h>
#include <window.h>
#include <object.h>
#include <camera.h>
#include <update.h>
#include <octree.h>
#include <input.h>
#include <shader.h>

// Is app paused. Initially set to false.
bool isPaused = false;

// Is app running. Intially set to true.
bool isRunning = true;

int frames = 0;

// Pauses (unpauses) the game and deattaches (attaches) the mouse cursor
void togglePause() {
    // Unpauses and returns cursor in the middle
    if (isPaused) {
        isPaused = false;
        glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    }
    // Pauses and makes cursor visible and not attached to the middle of screen
    else {
        firstMouseInput = true; // Prevents camera following new cursor position after pause
        isPaused = true;
        glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
    }
} 

// Main render function
void render() {
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glUseProgram(mainShader);

    setViewUniform(mainShader);

    // Apply linear interpolation to camera movement
    glm_vec3_lerp(camera.currPos, camera.targetPos, deltaTime * INTERPOLATION_MULTIPLIER, camera.currPos);
	
    //glm_vec3_copy(camera.targetPos, camera.currPos);

    // Rendering every object
    for (int i = 0; i < active_objects; i++) {
        setModelUniform(objects[i]->model, mainShader);
        glBindTexture(GL_TEXTURE_2D, objects[i]->texture.glName);
        glBindVertexArray(objects[i]->VAO);
        glDrawArrays(GL_TRIANGLES, 0, 36);
    }

    drawSkybox();

    // Debug: recursively draw octree border lines
    if (dbgRenderOctree)
        octreeDraw(root);

    frames++;
}

// Prints FPS every second
void showFPS() {
    if (glfwGetTime() - timer > 1) {
        printf("FPS: %d, Updates: %d\n", frames, updates);
        timer += 1;
        frames = 0;
        updates = 0;
    }
}
