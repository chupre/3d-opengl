// Max GLFW keycode
#define NUMBER_OF_KEYS 348 

// Keymap for keys.
// Key code == key index.
// Stores true if pressed, false if not.
bool keys[NUMBER_OF_KEYS];

// Apply user input to game logic
void processKeyboardInput()
{
    for (int i = 0; i < NUMBER_OF_KEYS; i++)
    {
        if (keys[i])
        {
            switch(i)
            {
                // Movement
                case GLFW_KEY_W:
                    moveCameraTarget(FORWARD);
                    break;

                case GLFW_KEY_S:
                    moveCameraTarget(BACKWARDS);
                    break;

                case GLFW_KEY_A:
                    moveCameraTarget(LEFT);
                    break;

                case GLFW_KEY_D:
                    moveCameraTarget(RIGHT);
                    break;

                case GLFW_KEY_LEFT_SHIFT:
                    camera.speedMultiplier = 2.0f;
                    break;
            }
        }
    }
}