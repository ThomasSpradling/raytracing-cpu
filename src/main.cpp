#include "Camera.h"
#include "HittableList.h"
#include "Image.h"
#include "Sphere.h"
#include <memory>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <vcruntime_typeinfo.h>

#define LOG_PROGRESS

int main() {
    constexpr int IMAGE_WIDTH = 400;
    constexpr float ASPECT_RATIO = 16.0f / 9.0f;

    Camera camera(IMAGE_WIDTH, ASPECT_RATIO);
    
    /*
        Now we create our world.
    */
    HittableList world;
    world.Add(std::make_shared<Sphere>(glm::vec3(0.0f, 0.0f, -1.0f), 0.5f));
    world.Add(std::make_shared<Sphere>(glm::vec3(0.0f, -100.5f, -1.0f), 100.0f));

    Image image = camera.Render(world);
    image.WriteToFile(PNG_OUTPUT_DIRECTORY "bozooo.png");
}
