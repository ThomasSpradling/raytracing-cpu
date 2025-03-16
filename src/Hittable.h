#pragma once

#include "Interval.h"
#include "Ray.h"
#include "glm/geometric.hpp"

struct Interesection {
    glm::vec3 point;
    float t = 0.0f;
    glm::vec3 normal;

    bool frontFace = false;

    /*
        Ensure the normal always faces the direction against the ray
    */
    void SetFaceNormal(const Ray &ray, const glm::vec3 &outwardNormal) {
        frontFace = glm::dot(ray.GetDirection(), outwardNormal) < 0;
        normal = frontFace ? outwardNormal : -outwardNormal;
    }
};

class Hittable {
public:
    virtual ~Hittable() = default;
    virtual bool Hit(const Ray &ray, Interval range, Interesection &intersection) const = 0;
};

