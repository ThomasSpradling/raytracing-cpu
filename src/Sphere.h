#pragma once

#include "Hittable.h"
#include "Interval.h"
#include "glm/common.hpp"

class Sphere : public Hittable {
public:
    Sphere(const glm::vec3 &center, float radius)
        : m_center(center), m_radius(glm::max(0.0f, radius)) {}

    bool Hit(const Ray &ray, Interval range, Interesection &intersection) const override;
private:
    glm::vec3 m_center;
    float m_radius;
};

