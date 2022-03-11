#include "object2D.h"

#include <vector>

#include "core/engine.h"
#include "utils/gl_utils.h"
# define pi (3.15159265359f)

Mesh* object2D::CreateSquare(
    const std::string &name,
    glm::vec3 leftBottomCorner,
    float length,
    glm::vec3 color,
    bool fill)
{
    glm::vec3 corner = leftBottomCorner;

    std::vector<VertexFormat> vertices =
    {
        VertexFormat(corner, color),
        VertexFormat(corner + glm::vec3(length, 0, 0), color),
        VertexFormat(corner + glm::vec3(length, length, 0), color),
        VertexFormat(corner + glm::vec3(0, length, 0), color)
    };

    Mesh* square = new Mesh(name);
    std::vector<unsigned int> indices = { 0, 1, 2, 3 };

    if (!fill) {
        square->SetDrawMode(GL_LINE_LOOP);
    } else {
        indices.push_back(0);
        indices.push_back(2);
    }

    square->InitFromData(vertices, indices);
    return square;
}

Mesh* object2D::CreateCircle(
    const std::string &name, 
    glm::vec3 circleCenter, 
    float radius, 
    glm::vec3 color, 
    bool fill,
    bool visible)
{
    std::vector<VertexFormat> vertices;
    std::vector<unsigned int> indices;
    glm::vec3 center = circleCenter;

    for (int i = 0; i < 360; i++) {
        float i_rad = i * 3.14159 / 180;
        vertices.push_back(VertexFormat(center + glm::vec3(radius * cos(i_rad), radius * sin(i_rad), 0), color));
    }

    indices.push_back(0);

    for (unsigned short i = 0; i < 360; i++)
        indices.push_back(i);

    Mesh* circle = new Mesh(name);

    if (!fill) {
        circle->SetDrawMode(GL_LINE_LOOP);
    }
    else {
        indices.push_back(0);
        indices.push_back(2);
    }
    if (visible == true) circle->InitFromData(vertices, indices);
    circle->SetDrawMode(GL_TRIANGLE_FAN);
    return circle;
}
