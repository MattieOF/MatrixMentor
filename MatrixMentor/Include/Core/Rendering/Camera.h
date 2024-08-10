#pragma once

#include "Core/Entity/Entity.h"

class Camera : Entity
{
public:
    Camera() = default;
    Camera(const float fov, const float nearPlane, const float farPlane)
    : FOV(fov), NearPlane(nearPlane), FarPlane(farPlane) {}
    Camera(const float fov, const float nearPlane, const float farPlane, const Transform& transform)
        : Entity(transform, nullptr), FOV(fov), NearPlane(nearPlane), FarPlane(farPlane) {}

    [[nodiscard]] glm::mat4 GetProjectionMatrix(const float aspectRatio) const
    {
        // TODO: Should we cache this?
        // Recalculating every frame may be faster due to cache misses of checking if the matrix has changed
        return glm::perspective(glm::radians(FOV), aspectRatio, NearPlane, FarPlane);
    }
    
    float FOV = 90;
    float NearPlane = 0.1f;
    float FarPlane = 1000.0f;
};
