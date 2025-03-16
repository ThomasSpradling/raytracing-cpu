#include "image.h"
#include <cstdio>
#include <format>
#include <iostream>
#include <ostream>

#define LOG_PROGRESS

int main() {
    constexpr int WIDTH = 256;
    constexpr int HEIGHT = 256;

    Image image(WIDTH, HEIGHT);

#ifdef LOG_PROGRESS
    std::cout << "Generating image..." << std::endl;
#endif

    int totalSamples = WIDTH * HEIGHT;
    int samplesComplete = 0;
    for (int j = 0; j < HEIGHT; ++j) {
        for (int i = 0; i < WIDTH; ++i) {
            auto r = static_cast<float>(i) / (WIDTH - 1);
            auto g = static_cast<float>(j) / (HEIGHT - 1);
            auto b = 0.0f;
                        
            image.SetPixel(i, j, glm::vec3(r, g, b));

            samplesComplete++;

#ifdef LOG_PROGRESS
            float percentage = static_cast<float>(samplesComplete) / totalSamples * 100;
            std::cout << std::format("\rCompleted {} / {} samples. [{:.2f}%]", samplesComplete, totalSamples, percentage);
#endif
        }
    }

#ifdef LOG_PROGRESS
    std::cout << "\nDone. \n";
#endif

    image.WriteToFile(PNG_OUTPUT_DIRECTORY "01_gradient.png");
}
