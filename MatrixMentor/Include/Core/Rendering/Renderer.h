#pragma once

// Forward declarations
class Camera;
class ShaderProgram;
class StaticShader;
class Entity;
class RawModel;
class TexturedModel;

class Renderer
{
public:
	FORCEINLINE static void  SetAspectRatio(float aspectRatio) { m_AspectRatio = aspectRatio; }
	FORCEINLINE static float GetAspectRatio() { return m_AspectRatio; }

	FORCEINLINE static void ResetClearColor() { m_ClearColor = glm::vec4(0.1f, 0.1f, 0.1f, 1.0f); }
	FORCEINLINE static void SetClearColor(glm::vec4 color) { m_ClearColor = color; }

	static void Prepare();
	static void Begin(const Camera* camera);
	static void End();
	static void Shutdown();

	static void RenderModel(const RawModel* model);
	static void RenderTexturedModel(const TexturedModel* model);
	static void RenderEntity(const Entity* entity, const StaticShader* shader);

	static void BindShader(const ShaderProgram* shader);

private:
	static glm::vec4            m_ClearColor;
	static float                m_AspectRatio;
	static const Camera*        m_CurrentCamera;
	static const ShaderProgram* m_BoundShader;
};
