// Window initialization
GLint window_width = 800, window_height = 600;
GLchar* window_name = "3D-OpenGL";
GLFWwindow* window;

GLvoid setWindow();

// GLFW & GLAD initialization and creating a window
GLvoid setWindow()
{
    //GLFW intialization and window settings
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

    // Setting window
    window = glfwCreateWindow(window_width, window_height, window_name, NULL, NULL);
    glfwMakeContextCurrent(window);
    gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
    glViewport(0, 0, window_width, window_height);
    glEnable(GL_DEPTH_TEST);
    
    //Setting icon for window
    GLint iconWidth, iconHeight;
    GLint channels;
    unsigned char* pixels = stbi_load("../resources/icons/window_icon.png", &iconWidth, &iconHeight, &channels, 4);

    GLFWimage images[1];
    images[0].width = iconWidth;
    images[0].height = iconHeight;
    images[0].pixels = pixels;
    glfwSetWindowIcon(window, 1, images);
}   