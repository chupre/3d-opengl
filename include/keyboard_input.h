// Standard includes
#include <stdbool.h>
#include <string.h>

// External 
#include <glad/glad.h>
#include <GLFW/glfw3.h>

// Max GLFW keycode
#define NUMBER_OF_KEYS 348 

// Keymap for keys.
// Key code == key index.
// Stores true if pressed, false if not.
extern bool keys[NUMBER_OF_KEYS];

void processKeyboardInput();