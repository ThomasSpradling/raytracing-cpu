#include "HittableList.h"
#include "Hittable.h"

HittableList::HittableList(const std::shared_ptr<Hittable> &object) {
    Add(object);
}

void HittableList::Clear() {
    m_objects.clear();
}

void HittableList::Add(const std::shared_ptr<Hittable> &object) {
    m_objects.push_back(object);
}

bool HittableList::Hit(const Ray &ray, Interval range, Interesection &intersection) const {
    Interesection temp;
    bool result = false;

    double closestDistance = range.max;
    for (const auto &object : m_objects) {
        if (object->Hit(ray, Interval(range.min, closestDistance), temp)) {
            result = true;
            closestDistance = temp.t;
            intersection = temp;
        }
    }

    return result;
}


