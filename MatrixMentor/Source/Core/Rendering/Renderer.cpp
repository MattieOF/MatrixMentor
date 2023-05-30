#include "mmpch.h"

#include "Core/Rendering/Renderer.h"

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
