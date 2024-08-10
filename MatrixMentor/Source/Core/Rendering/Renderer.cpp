#include "mmpch.h"

#include "Core/Rendering/Renderer.h"

#include "Core/Entity/Entity.h"
#include "Core/Rendering/Camera.h"
#include "Core/Rendering/RawModel.h"
#include "Core/Rendering/TexturedModel.h"
#include "Core/Rendering/Shaders/StaticShader.h"

#include "glad/gl.h"

const ShaderProgram* Renderer::m_BoundShader   = nullptr;
const Camera*        Renderer::m_CurrentCamera = nullptr;
float			     Renderer::m_AspectRatio   = 1.f;

void Renderer::Prepare()
{
	glClearColor(0.1f, 0.2f, 0.8f, 1.f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
}

void Renderer::Begin(const Camera* camera)
{
	MM_ASSERT_ERROR(camera, "Renderer::Begin called with nullptr Camera!");
	
	m_CurrentCamera = camera;
	
	if (m_BoundShader)
	{
		StaticShader* staticShader = dynamic_cast<StaticShader*>(const_cast<ShaderProgram*>(m_BoundShader));
		if (staticShader != nullptr)
		{
			staticShader->LoadProjectionMatrix(m_CurrentCamera->GetProjectionMatrix(m_AspectRatio));
			staticShader->LoadViewMatrix(m_CurrentCamera->GetViewMatrix());
		}
	}
}

void Renderer::End()
{
	m_CurrentCamera = nullptr;
	
	if (m_BoundShader)
	{
		StaticShader* staticShader = dynamic_cast<StaticShader*>(const_cast<ShaderProgram*>(m_BoundShader));
		if (staticShader != nullptr)
		{
			staticShader->LoadProjectionMatrix(glm::mat4()); // Reset projection matrix by passing identity matrix
			staticShader->LoadViewMatrix(glm::mat4()); // Same for view matrix	
		}
	}
}

void Renderer::Shutdown()
{
	m_CurrentCamera = nullptr;
	m_BoundShader = nullptr;
	m_AspectRatio = 0;
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
	MM_ASSERT_ERROR(entity, "Renderer::RenderEntity called with nullptr Entity!");
	MM_ASSERT_ERROR(shader, "Renderer::RenderEntity called with nullptr Shader!");

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

	if (m_CurrentCamera != nullptr)
	{
		StaticShader* staticShader = dynamic_cast<StaticShader*>(const_cast<ShaderProgram*>(shader));
		if (staticShader != nullptr)
		{
			staticShader->LoadProjectionMatrix(m_CurrentCamera->GetProjectionMatrix(m_AspectRatio));
			staticShader->LoadViewMatrix(m_CurrentCamera->GetViewMatrix());
		}
	}
}
