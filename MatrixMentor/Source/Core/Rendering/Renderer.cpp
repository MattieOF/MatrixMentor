#include "mmpch.h"

#include "Core/Rendering/Renderer.h"

#include "glad/gl.h"

void Renderer::Prepare()
{
	glClearColor(0.1f, 0.2f, 0.8f, 1.f);
	glClear(GL_COLOR_BUFFER_BIT);
}

void Renderer::RenderModel(RawModel* model)
{
	glBindVertexArray(model->GetVAO());
	glDrawArrays(GL_TRIANGLES, 0, static_cast<GLsizei>(model->GetVertexCount()));
	glBindVertexArray(0);
}
