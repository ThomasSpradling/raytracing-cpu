#include "image.h"
#include <cstdio>

int main() {
    constexpr int WIDTH = 256;
    constexpr int HEIGHT = 256;

    Image image(WIDTH, HEIGHT);

    for (int j = 0; j < HEIGHT; ++j) {
        for (int i = 0; i < WIDTH; ++i) {
            auto r = static_cast<float>(i) / (WIDTH - 1);
            auto g = static_cast<float>(j) / (HEIGHT - 1);
            auto b = 0.0f;

            Color color(r, g, b);
            image.SetPixel(i, j, color);
        }
    }

    image.WriteToFile(PNG_OUTPUT_DIRECTORY "01_gradient.png");
}
