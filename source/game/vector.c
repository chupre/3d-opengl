// Custom modules
#include <vector.h>

void newVec3(vec3 dest, float x, float y, float z) {
    vec3 new = { x, y, z };
    glm_vec3_copy(new, dest);
}