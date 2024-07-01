// Standard includes
#include <stdbool.h>

// External
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stb/stb_image.h>

// Window preinitialization
extern GLchar* window_name;
extern GLFWwindow* window;

// Window size
#define WINDOW_WIDTH 1280
#define WINDOW_HEIGHT 960
extern GLint screenWidth;
extern GLint screenHeight;

// Cursor position centered in middle
extern GLfloat lastCursorPosX;
extern GLfloat lastCursorPosY;

extern bool firstMouseInput;

GLvoid setWindow();
GLvoid keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
GLvoid mouseCallback(GLFWwindow* window, double xpos, double ypos);
GLvoid scrollCallback(GLFWwindow* window, double xoffset, double yoffset);
GLvoid quit();
