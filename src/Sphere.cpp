#include "Sphere.h"
#include "Interval.h"

bool Sphere::Hit(const Ray &ray, Interval range, Interesection &intersection) const {
    glm::vec3 co = m_center - ray.GetOrigin();

    float a = glm::dot(ray.GetDirection(), ray.GetDirection());
    float b = -glm::dot(ray.GetDirection(), co);
    float c = glm::dot(co, co) - m_radius * m_radius;

    float discriminant = b*b - a*c;
    if (discriminant < 0)
        return false;

    float sqrtDisc = glm::sqrt(discriminant);
    float root = (-b - sqrtDisc) / a;
    if (!range.contains(root)) {
        root = (-b + sqrtDisc) / a;
        if (!range.contains(root)) {
            return false;
        }
    }

    intersection.t = root;
    intersection.point = ray.At(intersection.t);
    glm::vec3 normal = (intersection.point - m_center) / m_radius;
    intersection.SetFaceNormal(ray, normal);

    return true;
}

