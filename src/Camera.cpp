#include "Camera.h"
#include "Hittable.h"
#include <format>
#include <iostream>

#define LOG_PROGRESS

Camera::Camera(int imageWidth, float aspectRatio, float focalLength, float viewportHeight)
    : m_imageWidth(imageWidth),
      m_aspectRatio(aspectRatio),
      m_focalLength(focalLength),
      m_viewportHeight(viewportHeight),
      m_position(0.0f, 0.0f, 0.0f),
      m_du(1.0f, 0.0f, 0.0f),    // Right direction along +X
      m_dv(0.0f, -1.0f, 0.0f)    // Downward direction along -Y
{
    /*
        We define the camera center to be the point from which all rays originate. We point it
        down the -Z axis and keep a viewport along the XY plane. To orient things better,
        we position the viewport to be *focal length* in front of the camera (along the Z-axis)
        and such that its center has XY = (0, 0).
    */
    int tempHeight = static_cast<int>(m_imageWidth / m_aspectRatio);
    m_imageHeight = (tempHeight < 1) ? 1 : tempHeight;

    m_viewportWidth = m_viewportHeight * static_cast<float>(m_imageWidth) / m_imageHeight;

    m_pixelSizeU = m_viewportWidth / m_imageWidth;
    m_pixelSizeV = m_viewportHeight / m_imageHeight;

    m_viewportPosition = m_position - glm::vec3(0.0f, 0.0f, m_focalLength)
                         - (m_du * m_viewportWidth) / 2.0f
                         - (m_dv * m_viewportHeight) / 2.0f;

    m_deltaPixelU = m_du * m_pixelSizeU;
    m_deltaPixelV = m_dv * m_pixelSizeV;

    /*
        We grab the center of the first pixel: The top-left most position
    */
    m_firstPixelPos = m_viewportPosition + m_deltaPixelU * 0.5f + m_deltaPixelV * 0.5f;
}

void Camera::SetPosition(const glm::vec3 &position) {
    m_position = position;
    m_viewportPosition = m_position - glm::vec3(0.0f, 0.0f, m_focalLength)
                         - (m_du * m_viewportWidth) / 2.0f
                         - (m_dv * m_viewportHeight) / 2.0f;
    m_firstPixelPos = m_viewportPosition + m_deltaPixelU * 0.5f + m_deltaPixelV * 0.5f;
}

Image Camera::Render(const Hittable &world) {
#ifdef LOG_PROGRESS
    std::cout << "Generating image..." << std::endl;
    int totalSamples = m_imageWidth * m_imageHeight;
    int samplesComplete = 0;
#endif

    Image image(m_imageWidth, m_imageHeight);

    for (int j = 0; j < m_imageHeight; ++j) {
        for (int i = 0; i < m_imageWidth; ++i) {
            float x = static_cast<float>(i);
            float y = static_cast<float>(j);

            glm::vec3 currentPixelPos = m_firstPixelPos + x * m_deltaPixelU + y * m_deltaPixelV;
            glm::vec3 rayDirection = currentPixelPos - m_position;

            Ray ray(m_position, rayDirection);

            image.SetPixel(i, j, RayColor(ray, world));

#ifdef LOG_PROGRESS
            samplesComplete++;
            float percentage = static_cast<float>(samplesComplete) / totalSamples * 100;
            std::cout << std::format("\rCompleted {} / {} samples. [{:.2f}%]", samplesComplete, totalSamples, percentage);
#endif
        }
    }

#ifdef LOG_PROGRESS
    std::cout << "\nDone. \n";
#endif

    return image;
}

glm::vec3 Camera::RayColor(const Ray &ray, const Hittable &world) {
    Interesection intersection;
    if (world.Hit(ray, Interval(0, std::numeric_limits<float>::infinity()), intersection)) {
        return 0.5f * (intersection.normal + glm::vec3(1.0f));
    }

    glm::vec3 direction = glm::normalize(ray.GetDirection());
    auto a = 0.5f * (direction.y + 1.0f);
    return glm::mix(glm::vec3(1.0f), glm::vec3(0.5f, 0.7f, 1.0f), a);
}
