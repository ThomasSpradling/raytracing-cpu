#pragma once

#include <glm/glm.hpp>

class Ray {
public:
    Ray() = default;
    Ray(const glm::vec3 &origin, const glm::vec3 &direction)
        : m_origin(origin), m_direction(direction) {}

    inline const glm::vec3 &GetOrigin() const { return m_origin; }
    inline const glm::vec3 &GetDirection() const { return m_direction; }

    glm::vec3 At(float t) const;
private:
    glm::vec3 m_origin;
    glm::vec3 m_direction;
};
