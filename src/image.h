#pragma once

#include <cstdint>
#include <string>
#include <vector>

#include <glm/glm.hpp>

class Image {
public:
    Image(int width, int height);
    ~Image();

    void WriteToFile(const std::string &path);
    static Image FromFile(const std::string &path);

    void SetPixel(int x, int y, const glm::vec3 &color);
private:
    static constexpr int FORMAT_SIZE = 3;
    const int m_width;
    const int m_height;
    // m_data;

    struct Color {
        uint8_t r = 0;
        uint8_t g = 0;
        uint8_t b = 0;
    
        Color() : Color(0, 0, 0) {}
    
        explicit Color(int r, int g, int b)
            : r(r), g(g), b(b) {}
    
        explicit Color(float r, float g, float b)
            : r(r * 255), g(g * 255), b(b * 255)
        {
            assert(r >= 0.0f && r <= 1.0f);
            assert(g >= 0.0f && g <= 1.0f);
            assert(b >= 0.0f && b <= 1.0f);

            this->r = static_cast<uint8_t>(r * 255);
            this->g = static_cast<uint8_t>(g * 255);
            this->b = static_cast<uint8_t>(b * 255);
        }
    };

    std::vector<Color> m_data;
};
