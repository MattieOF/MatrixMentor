#include "mmpch.h"

#include "Core/Rendering/Renderer.h"
#include "Core/Rendering/RawModel.h"
#include "Core/Rendering/TexturedModel.h"

#include "glad/gl.h"

void Renderer::Prepare()
{
	glClearColor(0.1f, 0.2f, 0.8f, 1.f);
	glClear(GL_COLOR_BUFFER_BIT);
}

void Renderer::RenderModel(const RawModel* model)
{
	glBindVertexArray(model->GetVAO());
	glEnableVertexAttribArray(0);
	glDrawElements(GL_TRIANGLES, static_cast<GLsizei>(model->GetVertexCount()), GL_UNSIGNED_INT, nullptr);
	glDisableVertexAttribArray(0);
	glBindVertexArray(0);
}

void Renderer::RenderTexturedModel(const TexturedModel *model)
{
    glBindVertexArray(model->GetModel()->GetVAO());
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
    model->GetTexture()->Activate(0);
    glDrawElements(GL_TRIANGLES, static_cast<GLsizei>(model->GetModel()->GetVertexCount()), GL_UNSIGNED_INT, nullptr);
    glDisableVertexAttribArray(1);
    glDisableVertexAttribArray(0);
    glBindVertexArray(0);
}
