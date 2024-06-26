#define DEFAULT_FOV 60.0f
#define DEFAULT_CAMERA_SPEED_MULTIPLIER 2.0f
#define DEFAULT_CAMERA_SPEED 40.0f
#define INTERPOLATION_STEP 0.05f

// Consts for transformations around x, y, z 
vec3 X_AXIS = { 1.0f, 0.0f, 0.0f };
vec3 Y_AXIS = { 0.0f, 1.0f, 0.0f };
vec3 Z_AXIS = { 0.0f, 0.0f, 1.0f };

// Camera offset by mouse input
GLfloat pitch = 0.0f;
GLfloat yaw = -90.0f;

void initCamera();
void setModelUniform();
void setViewUniform();
void setProjectionUniform();
void moveCameraTarget(enum moveDirection dir);
void applyMouseInput();

// Camera initialization
void initCamera()
{
    camera.FOV = DEFAULT_FOV;
    camera.speedMultiplier = 1.0f;

    // Setting camera vectors
    vec3 pos = { 0.0f, 1.0f, 3.0f };
    vec3 front = { 0.0f, 0.0f, -1.0f };
    vec3 up = { 0.0f, 1.0f, 0.0f };
    glm_vec3_copy(pos, camera.currPos);
    glm_vec3_copy(pos, camera.targetPos);
    glm_vec3_copy(front, camera.front);
    glm_vec3_copy(up, camera.up);
}

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
    glm_vec3_add(camera.currPos, camera.front, temp);
    glm_lookat(camera.currPos, temp, camera.up, view);

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
    glm_perspective(glm_rad(camera.FOV), (float)screenWidth / (float)screenHeight, 0.1f, 100.0f, projection);

    // Setting projection uniform
    int projectionLoc = glGetUniformLocation(shaderProgram, "projection");
    glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, projection);
}

// Updates camera target position
void moveCameraTarget(enum moveDirection dir)
{
    // Speeds multiplies by deltatime to make it not fps-related
    float cameraSpeed = DEFAULT_CAMERA_SPEED * deltaTime * camera.speedMultiplier;
    vec3 temp;

    // Move camera forwards
    if (dir == FORWARD)
    {
        glm_vec3_scale(camera.front, cameraSpeed, temp);
        glm_vec3_add(camera.currPos, temp, camera.targetPos);
    }

    // Move camera backwards
    if (dir == BACKWARDS)
    {
        glm_vec3_scale(camera.front, cameraSpeed, temp);
        glm_vec3_sub(camera.currPos, temp, camera.targetPos);
    }

    // Move camera to the right
    if (dir == RIGHT)
    {
        glm_vec3_cross(camera.front, camera.up, temp);
        glm_normalize(temp);
        glm_vec3_scale(temp, cameraSpeed, temp);
        glm_vec3_add(camera.currPos, temp, camera.targetPos);
    }

    // Move camera to the left
    if (dir == LEFT)
    {
        glm_vec3_cross(camera.front, camera.up, temp);
        glm_normalize(temp);
        glm_vec3_scale(temp, cameraSpeed, temp);
        glm_vec3_sub(camera.currPos, temp, camera.targetPos);
    }

    // No flying
    //targetPos[1] = 1.0f; 

    updateCameraPosition();
    camera.speedMultiplier = 1.0f;
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
    glm_normalize_to(direction, camera.front);
}
