// Custom modules
#include <window.h>
#include <input.h>
#include <shader.h>
#include <collision.h>

// Window preinitialization
GLchar* window_name = "3D-OpenGL";
GLFWwindow* window;

GLint screenWidth = WINDOW_WIDTH;
GLint screenHeight = WINDOW_HEIGHT;

// GLFW & GLAD initialization and creating a window
GLvoid setWindow() {
    //GLFW intialization and window settings
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
    glfwWindowHint(GLFW_SAMPLES, 4);

    // Setting window
    window = glfwCreateWindow(screenWidth, screenHeight, window_name, NULL, NULL);
    glfwMakeContextCurrent(window);
    gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
    glViewport(0, 0, screenWidth, screenHeight);
    glEnable(GL_DEPTH_TEST);

    // Turn on MSAA
    glEnable(GL_MULTISAMPLE);

    // Disable vsync
    glfwSwapInterval(1);

    //Setting icon for window
    GLint iconWidth, iconHeight;
    GLint channels;
    unsigned char* pixels = stbi_load("../resources/icons/window_icon.png", &iconWidth, &iconHeight, &channels, 4);
    GLFWimage images[1];
    images[0].width = iconWidth;
    images[0].height = iconHeight;
    images[0].pixels = pixels; 
    glfwSetWindowIcon(window, 1, images);
    stbi_image_free(pixels);

    // Setting input callbacks
    glfwSetKeyCallback(window, keyCallback);
    glfwSetCursorPosCallback(window, mouseCallback);
    glfwSetScrollCallback(window, scrollCallback);

    // Keeps cursor in center of the window in order to use mouse for camera input
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    // Initialize keymap
    memset(keys, false, sizeof(keys));
}  

// Close program
GLvoid quit() {
    glDeleteProgram(shaderProgram);
    glfwTerminate();
    exit(EXIT_SUCCESS);
}