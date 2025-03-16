#pragma once

#include "Hittable.h"
#include "Image.h"

class Camera {
public:
    Camera(int width, float aspect, float focalLength = 1.0f, float viewportHeight = 2.0f);

    void SetPosition(const glm::vec3 &position);
    
    Image Render(const Hittable &world);

    inline int GetImageWidth() const { return m_imageWidth; }
    inline int GetImageHeight() const { return m_imageHeight; }

private:
    int m_imageWidth;
    float m_aspectRatio;
    int m_imageHeight;
    
    float m_focalLength;

    float m_viewportHeight;
    float m_viewportWidth;

    float m_pixelSizeU;
    float m_pixelSizeV;
    
    glm::vec3 m_position;
    
    glm::vec3 m_du; 
    glm::vec3 m_dv; 

    glm::vec3 m_viewportPosition;

    glm::vec3 m_deltaPixelU;
    glm::vec3 m_deltaPixelV;

    glm::vec3 m_firstPixelPos;

    void Initialize();

    /*
        Computes the color returned by a given ray.
    */
    glm::vec3 RayColor(const Ray &ray, const Hittable &world);
};
