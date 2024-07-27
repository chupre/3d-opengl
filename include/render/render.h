// Standars includes
#include <stdbool.h>
#include <stdio.h>

// External
#include <glad/glad.h>
#include <GLFW/glfw3.h>

extern int frames;

// Is app paused. Initially set to false.
extern bool isPaused;

// Is app running. Intially set to true.
extern bool isRunning;

void showFPS();
void togglePause();
void render();
