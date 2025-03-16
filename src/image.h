#pragma once

#include <cstdint>
#include <string>
#include <vector>

struct Color {
    uint8_t r = 0;
    uint8_t g = 0;
    uint8_t b = 0;

    Color() : Color(0, 0, 0) {}

    explicit Color(int r, int g, int b)
        : r(r), g(g), b(b) {}

    explicit Color(float r, float g, float b)
        : r(r * 255), g(g * 255), b(b * 255) {}
};

class Image {
public:
    Image(int width, int height);
    ~Image();

    void WriteToFile(const std::string &path);
    static Image FromFile(const std::string &path);

    void SetPixel(int x, int y, const Color &color);
private:
    static constexpr int FORMAT_SIZE = 3;
    const int m_width;
    const int m_height;
    // m_data;

    std::vector<Color> m_data;
};
