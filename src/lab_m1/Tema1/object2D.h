#pragma once

#include <string>

#include "core/gpu/mesh.h"
#include "utils/glm_utils.h"


namespace object2D
{
    Mesh* CreateSquare(const std::string &name, glm::vec3 leftBottomCorner, float length, glm::vec3 color, bool fill);
    Mesh* CreateCircle(const std::string &name, glm::vec3 circleCenter, float radius, glm::vec3 color, bool fill, bool visible);
}
