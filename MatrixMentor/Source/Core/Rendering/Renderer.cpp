#include "mmpch.h"

#include "Core/Rendering/Renderer.h"

#include "Core/Entity/Entity.h"
#include "Core/Rendering/RawModel.h"
#include "Core/Rendering/TexturedModel.h"
#include "Core/Rendering/Shaders/StaticShader.h"

#include "glad/gl.h"

const ShaderProgram* Renderer::m_BoundShader = nullptr;

void Renderer::Prepare()
{
	glClearColor(0.1f, 0.2f, 0.8f, 1.f);
	glClear(GL_COLOR_BUFFER_BIT);
}

void Renderer::RenderModel(const RawModel* model)
{
	MM_ASSERT_ERROR(model, "Renderer::RenderModel called with nullptr RawModel!");
	glBindVertexArray(model->GetVAO());
	glEnableVertexAttribArray(0);
	glDrawElements(GL_TRIANGLES, static_cast<GLsizei>(model->GetVertexCount()), GL_UNSIGNED_INT, nullptr);
	glDisableVertexAttribArray(0);
	glBindVertexArray(0);
}

void Renderer::RenderTexturedModel(const TexturedModel *model)
{
	MM_ASSERT_ERROR(model, "Renderer::RenderTexturedModel called with nullptr TexturedModel!");
    glBindVertexArray(model->GetModel()->GetVAO());
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
    model->GetTexture()->Activate(0);
    glDrawElements(GL_TRIANGLES, static_cast<GLsizei>(model->GetModel()->GetVertexCount()), GL_UNSIGNED_INT, nullptr);
    glDisableVertexAttribArray(1);
    glDisableVertexAttribArray(0);
    glBindVertexArray(0);
}

void Renderer::RenderEntity(const Entity* entity, const StaticShader* shader)
{
	if (!entity->GetModel())
		return;

	if (m_BoundShader != shader)
		BindShader(shader);
	
	shader->LoadTransformationMatrix(entity->GetTransform().GetTransformationMatrix());
	RenderTexturedModel(entity->GetModel().get());
}

void Renderer::BindShader(const ShaderProgram* shader)
{
	shader->Bind();
	m_BoundShader = shader;
}
