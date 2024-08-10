#pragma once

class Camera;
// Forward declarations
class ShaderProgram;
class StaticShader;
class Entity;
class RawModel;
class TexturedModel;

class Renderer
{
public:
	FORCEINLINE static void  SetAspectRatio(float aspectRatio) { m_AspectRatio = aspectRatio; }
	FORCEINLINE static float GetAspectRatio()                  { return m_AspectRatio; }
	
	static void Prepare();
	static void Begin(const Camera* camera);
	static void End();
	static void Shutdown();
	
	static void RenderModel(const RawModel* model);
    static void RenderTexturedModel(const TexturedModel* model);
    static void RenderEntity(const Entity* entity, const StaticShader* shader);

	static void BindShader(const ShaderProgram* shader);
	
private:
	static float m_AspectRatio;
	static const Camera* m_CurrentCamera;
	static const ShaderProgram* m_BoundShader;
};
