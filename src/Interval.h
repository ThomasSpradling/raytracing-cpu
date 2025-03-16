#pragma once

#include <limits>
struct Interval {
    float min = std::numeric_limits<float>::min();
    float max = std::numeric_limits<float>::max();

    Interval() = default;
    Interval(float min, float max) : min(min), max(max) {}

    inline float length() const { return max - min; }
    inline bool contains(float x) const { return min <= x && x <= max; }

    static const Interval empty, full;
};

inline const Interval Interval::empty = Interval(1.0f, -1.0f);
inline const Interval Interval::full = Interval();
