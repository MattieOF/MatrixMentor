#include "mmpch.h"
#include "Core/Rendering/TexturedModel.h"

TexturedModel::TexturedModel(Ref<RawModel> model, Ref<Texture> texture)
{
	m_Model   = std::move(model);
	m_Texture = std::move(texture);
}

TexturedModel::~TexturedModel()
{
}
