#include "mmpch.h"
#include "Core/Entity/Entity.h"

Entity::Entity()
{ }

Entity::Entity(const Ref<TexturedModel>& model)
	: m_Model(model)
{ }

Entity::Entity(const Transform& transform, const Ref<TexturedModel>& model)
	: m_Transform(transform), m_Model(model)
{ }
