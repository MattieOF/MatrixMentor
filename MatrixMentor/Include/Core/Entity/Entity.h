#pragma once

#include "Transform.h"

class TexturedModel;

class Entity
{
public:
	Entity();
	Entity(const Ref<TexturedModel>& model);
	Entity(const Transform& transform, const Ref<TexturedModel>& model);

	void                           SetTransform(const Transform& transform) { m_Transform = transform; }
	[[nodiscard]] Transform&       GetTransform() { return m_Transform; }
	[[nodiscard]] const Transform& GetTransform() const { return m_Transform; }

	void                                    SetModel(const Ref<TexturedModel>& model) { m_Model = model; }
	[[nodiscard]] const Ref<TexturedModel>& GetModel() const { return m_Model; }

protected:
	Transform          m_Transform;
	Ref<TexturedModel> m_Model;
};
