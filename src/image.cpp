#include "image.h"
#include <cstdio>

#define STB_IMAGE_IMPLEMENTATION
#include <stb/stb_image.h>

#define STB_IMAGE_WRITE_IMPLEMENTATION
#include <stb/stb_image_write.h>


Image::Image(int width, int height)
    : m_width(width)
    , m_height(height)
    , m_data(width * height * 3)
{}

Image::~Image() {
    m_data.clear();
}

void Image::WriteToFile(const std::string &path) {
    int result = stbi_write_png(path.c_str(), m_width, m_height, 3, m_data.data(), 3 * sizeof(uint8_t) * m_width);

    if (!result) {
        fprintf(stderr, "Failed to write file to path %s.", path.c_str());
    }
}

void Image::SetPixel(int x, int y, const Color &color) {
    m_data[m_width * y + x] = color;
}

Image Image::FromFile(const std::string &path) {
    int components, width, height;
    unsigned char *data = stbi_load(path.c_str(), &width, &height, &components, 3);

    if (!data) {
        fprintf(stderr, "Failed to load file from path %s", path.c_str());
    }

    assert(components == 3);
    assert(width >= 1);
    assert(height >= 1);

    Image image(width, height);
    for (int j = 0; j < height; ++j) {
        for (int i = 0; i < width; ++i) {
            Color color;
            color.r = data[3 * (width * j + i) + 0];
            color.g = data[3 * (width * j + i) + 1];
            color.b = data[3 * (width * j + i) + 2];

            image.SetPixel(i, j, color);
        }
    }

    return image;
}
