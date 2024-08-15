#pragma once

class Light
{
public:
	Light(const glm::vec3& position, const glm::vec3& color)
		: m_Position(position), m_Color(color) {}

	[[nodiscard]] const glm::vec3& GetPosition() const  { return m_Position; }
	[[nodiscard]] const glm::vec3& GetColor() const { return m_Color; }

	void SetPosition(const glm::vec3& position) { m_Position = position; }
	void SetColor(const glm::vec3& color) { m_Color = color; }
	
private:
	glm::vec3 m_Position;
	glm::vec3 m_Color;
};
