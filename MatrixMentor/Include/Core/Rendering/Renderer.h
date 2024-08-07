#pragma once

// Forward declarations
class RawModel;
class TexturedModel;

class Renderer
{
public:
	static void Prepare();
	static void RenderModel(const RawModel* model);
    static void RenderTexturedModel(const TexturedModel* model);
};
