#pragma once

#include "RawModel.h"
#include "Texture.h"

class TexturedModel
{
public:
	TexturedModel(Ref<RawModel> model, Ref<Texture> texture);
	~TexturedModel();

	[[nodiscard]] inline const Ref<RawModel>& GetModel()   const { return m_Model; }
	[[nodiscard]] inline const Ref<Texture>&  GetTexture() const { return m_Texture; }

private:
	Ref<RawModel> m_Model;
	Ref<Texture> m_Texture;
};
