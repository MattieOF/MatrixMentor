#include "mmpch.h"

#include "Core/Rendering/Camera.h"

#include "Core/Input/Input.h"

void Camera::DoDefaultMovement(float deltaTime)
{
	float speed = 5.0f;
	if (Input::IsKeyDown(MM_KEY_LEFT_CONTROL))
		speed *= 3.0f;
	
	if (Input::IsKeyDown(MM_KEY_W))
		m_Transform.Position.z -= deltaTime * speed;
	if (Input::IsKeyDown(MM_KEY_S))
		m_Transform.Position.z += deltaTime * speed;
	if (Input::IsKeyDown(MM_KEY_A))
		m_Transform.Position.x -= deltaTime * speed;
	if (Input::IsKeyDown(MM_KEY_D))
		m_Transform.Position.x += deltaTime * speed;

	if (Input::IsKeyDown(MM_KEY_Q))
		m_Transform.Rotation.y -= deltaTime * speed * 15;
	if (Input::IsKeyDown(MM_KEY_E))
		m_Transform.Rotation.y += deltaTime * speed * 15;

	if (Input::IsKeyDown(MM_KEY_SPACE))
		m_Transform.Position.y += deltaTime * speed;
	if (Input::IsKeyDown(MM_KEY_LEFT_SHIFT))
		m_Transform.Position.y -= deltaTime * speed;
}
