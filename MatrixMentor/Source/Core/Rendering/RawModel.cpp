#include "mmpch.h"

#include "Core/Rendering/RawModel.h"

#include "glad/gl.h"

RawModel::RawModel(const std::vector<float>& vertices)
{
	m_VAO = CreateEmptyVAO();
	VertexCount = static_cast<uint32_t>(vertices.size() / 3);
	glBindVertexArray(0);
}

RawModel::~RawModel()
{
	glDeleteVertexArrays(1, &m_VAO);
	glDeleteBuffers(static_cast<int>(m_VBOs.size()), m_VBOs.data());
}

void RawModel::StoreDataInAttributeList(uint32_t index, const std::vector<float>& data, int32_t dataSize)
{
	uint32_t vboId;
	glGenBuffers(1, &vboId);
	glBindBuffer(GL_ARRAY_BUFFER, vboId);
	glBufferData(GL_ARRAY_BUFFER, data.size() * sizeof(data[0]), data.data(), GL_STATIC_DRAW);
	glVertexAttribPointer(index, dataSize, GL_FLOAT, false, 0, nullptr);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

uint32_t RawModel::CreateEmptyVAO()
{
	uint32_t vao;
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	return vao;
}
