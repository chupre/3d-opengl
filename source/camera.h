#define DEFAULT_FOV 60.0f
#define INTERPOLATION_STEP 0.05f

// Consts for transformations around x, y, z 
vec3 X_AXIS = { 1.0f, 0.0f, 0.0f };
vec3 Y_AXIS = { 0.0f, 1.0f, 0.0f };
vec3 Z_AXIS = { 0.0f, 0.0f, 1.0f };

// Camera offset by mouse input
GLfloat pitch = 0.0f;
GLfloat yaw = -90.0f;

// Camera FOV
GLfloat fov = DEFAULT_FOV;

// Vectors for constructing view matrix
vec3 cameraPos = { 0.0f, 1.0f, 3.0f };
vec3 cameraFront = { 0.0f, 0.0f, -1.0f };
vec3 cameraUp = { 0.0f, 1.0f, 0.0f };

// Camera speed multiplier, initially set to 1.0, increases when shift is pressed
GLfloat cameraSpeedMultiplier = 1.0f;

void setModelUniform();
void setViewUniform();
void setProjectionUniform();
void moveCamera(enum moveDirection dir);
void applyMouseInput();

// Set model matrix uniform in vertex shader
void setModelUniform()
{
    // Creating model matrix
    mat4 model;
    glm_mat4_identity(model);
    glm_rotate(model, glm_rad(-90.0f), X_AXIS);

    // Setting model uniform
    int modelLoc = glGetUniformLocation(shaderProgram, "model");
    glUniformMatrix4fv(modelLoc, 1, GL_FALSE, model);
}

// Set view matrix uniform in vertex shader
void setViewUniform()
{
    // Creating view matrix
    mat4 view;
    vec3 temp;
    glm_vec3_add(cameraPos, cameraFront, temp);
    glm_lookat(cameraPos, temp, cameraUp, view);

    // Setting view uniform
    int viewLoc = glGetUniformLocation(shaderProgram, "view");
    glUniformMatrix4fv(viewLoc, 1, GL_FALSE, view);
}

// Set projection matrix uniform in vertex shader
void setProjectionUniform()
{
    // Creating projection matrix
    mat4 projection;
    glm_mat4_identity(projection);
    glm_perspective(glm_rad(fov), (float)screenWidth / (float)screenHeight, 0.1f, 100.0f, projection);

    // Setting projection uniform
    int projectionLoc = glGetUniformLocation(shaderProgram, "projection");
    glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, projection);
}

// Moving camera
void moveCamera(enum moveDirection dir)
{
    // Speeds multiplies by deltatime to make it not fps-related
    float cameraSpeed = 10.0f * deltaTime * cameraSpeedMultiplier;
    vec3 temp, targetPos;

    // Move camera forwards
    if (dir == FORWARD)
    {
        glm_vec3_scale(cameraFront, cameraSpeed, temp);
        glm_vec3_add(cameraPos, temp, targetPos);
    }

    // Move camera backwards
    if (dir == BACK)
    {
        glm_vec3_scale(cameraFront, cameraSpeed, temp);
        glm_vec3_sub(cameraPos, temp, targetPos);
    }

    // Move camera to the right
    if (dir == RIGHT)
    {
        glm_vec3_cross(cameraFront, cameraUp, temp);
        glm_normalize(temp);
        glm_vec3_scale(temp, cameraSpeed, temp);
        glm_vec3_add(cameraPos, temp, targetPos);
    }

    // Move camera to the left
    if (dir == LEFT)
    {
        glm_vec3_cross(cameraFront, cameraUp, temp);
        glm_normalize(temp);
        glm_vec3_scale(temp, cameraSpeed, temp);
        glm_vec3_sub(cameraPos, temp, targetPos);
    }

    glm_vec3_copy(targetPos, cameraPos);
}

// Updating camera position depending on mouse input
void applyMouseInput()
{
    // Calculating direction vector
    vec3 direction;
    direction[0] = cos(glm_rad(yaw)) * cos(glm_rad(pitch));
    direction[1] = sin(glm_rad(pitch));
    direction[2] = sin(glm_rad(yaw)) * cos(glm_rad(pitch));

    // Applying changes to camera position
    glm_normalize_to(direction, cameraFront);
}
