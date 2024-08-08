#pragma once

// Forward declarations
class ShaderProgram;
class StaticShader;
class Entity;
class RawModel;
class TexturedModel;

class Renderer
{
public:
	static void Prepare();
	static void RenderModel(const RawModel* model);
    static void RenderTexturedModel(const TexturedModel* model);
    static void RenderEntity(const Entity* entity, const StaticShader* shader);

	static void BindShader(const ShaderProgram* shader);
	
private:
	static const ShaderProgram* m_BoundShader;
};
