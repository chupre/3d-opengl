// Max GLFW keycode
#define NUMBER_OF_KEYS 348 

// Keymap for keys.
// Key code == key index.
// Stores true if pressed, false if not.
bool keys[NUMBER_OF_KEYS];

// Apply user input to game logic
void processKeyboardInput()
{
    // Resets camera directions
    memset(cameraMovement, false, sizeof(cameraMovement));

    for (int i = 0; i < NUMBER_OF_KEYS; i++)
    {
        // If key is pressed
        if (keys[i])
        {
            switch(i)
            {
                // Movement
                case GLFW_KEY_W:
                    cameraMovement[FORWARD] = true;
                    break;

                case GLFW_KEY_S:
                    cameraMovement[BACKWARDS] = true;
                    break;

                case GLFW_KEY_A:
                    cameraMovement[LEFT] = true;
                    break;

                case GLFW_KEY_D:
                    cameraMovement[RIGHT] = true;
                    break;

                case GLFW_KEY_LEFT_SHIFT:
                    camera.speedMultiplier = 2.0f;
                    break;
            }
        }
    }
}