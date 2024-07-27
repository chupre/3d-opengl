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
#define WINDOW_WIDTH 1920
#define WINDOW_HEIGHT 1080
extern GLint screenWidth;
extern GLint screenHeight;

GLvoid setWindow();
GLvoid quit();
