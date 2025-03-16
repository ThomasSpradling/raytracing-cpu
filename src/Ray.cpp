#include "Ray.h"

glm::vec3 Ray::At(float t) const {
    return m_origin + t * m_direction;
}
