#pragma once

#include "Hittable.h"
#include "Interval.h"
#include <memory>

class HittableList : public Hittable {
public:
    HittableList() = default;
    HittableList(const std::shared_ptr<Hittable> &object);

    void Clear();
    void Add(const std::shared_ptr<Hittable> &object);

    bool Hit(const Ray &ray, Interval range, Interesection &intersection) const override;
private:
    std::vector<std::shared_ptr<Hittable>> m_objects;
};

