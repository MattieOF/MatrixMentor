#pragma once

#include "Core/Entity/Entity.h"

class Camera : public Entity
{
public:
	Camera() = default;

	Camera(const float fov, const float nearPlane, const float farPlane)
		: FOV(fov), NearPlane(nearPlane), FarPlane(farPlane)
	{
	}

	Camera(const float fov, const float nearPlane, const float farPlane, const Transform& transform)
		: Entity(transform, nullptr), FOV(fov), NearPlane(nearPlane), FarPlane(farPlane)
	{
	}

	[[nodiscard]] glm::mat4 GetProjectionMatrix(const float aspectRatio) const
	{
		// TODO: Should we cache this?
		// Recalculating every frame may be faster due to cache misses of checking if the matrix has changed
		return glm::perspective(glm::radians(FOV), aspectRatio, NearPlane, FarPlane);
	}

	[[nodiscard]] glm::mat4 GetViewMatrix() const
	{
		auto viewMatrix = glm::mat4(1.0f);
		viewMatrix      = rotate(viewMatrix, glm::radians(GetTransform().Rotation.x), glm::vec3(1, 0, 0));
		viewMatrix      = rotate(viewMatrix, glm::radians(GetTransform().Rotation.y), glm::vec3(0, 1, 0));
		viewMatrix      = rotate(viewMatrix, glm::radians(GetTransform().Rotation.z), glm::vec3(0, 0, 1));
		viewMatrix      = translate(viewMatrix, -GetTransform().Position);
		return viewMatrix;
	}

	float FOV       = 90;
	float NearPlane = 0.1f;
	float FarPlane  = 1000.0f;
};
