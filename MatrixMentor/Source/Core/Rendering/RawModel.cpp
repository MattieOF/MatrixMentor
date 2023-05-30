#include "mmpch.h"

#include "Core/Rendering/RawModel.h"

#include "glad/gl.h"

RawModel::RawModel(const std::vector<float>& vertices, const std::vector<uint32_t>& indices)
{
	m_VAO = CreateEmptyVAO();
	m_VertexCount = static_cast<uint32_t>(indices.size());
	BindIndiciesBuffer(indices);
	StoreDataInAttributeList(0, vertices, 3);
	glBindVertexArray(0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0); // Unbind IBO after unbinding VBO, or it'll unbind the IBO from the VBO
}

RawModel::~RawModel()
{
	glDeleteVertexArrays(1, &m_VAO);
	glDeleteBuffers(1, &m_IBO);
	glDeleteBuffers(static_cast<int>(m_VBOs.size()), m_VBOs.data());
}

void RawModel::BindIndiciesBuffer(const std::vector<uint32_t>& indices)
{
	if (m_IBO != 0)
		glDeleteBuffers(1, &m_IBO);
	glGenBuffers(1, &m_IBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_IBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(indices[0]), indices.data(), GL_STATIC_DRAW);
}

void RawModel::StoreDataInAttributeList(uint32_t index, const std::vector<float>& data, int32_t dataSize)
{
	uint32_t vboId;
	glGenBuffers(1, &vboId);
	m_VBOs.emplace_back(vboId);
	glBindBuffer(GL_ARRAY_BUFFER, vboId);
	glBufferData(GL_ARRAY_BUFFER, data.size() * sizeof(data[0]), data.data(), GL_STATIC_DRAW);
	glEnableVertexAttribArray(index);
	glVertexAttribPointer(index, dataSize, GL_FLOAT, false, 0, nullptr);
	glDisableVertexAttribArray(index);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

uint32_t RawModel::CreateEmptyVAO()
{
	uint32_t vao;
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	return vao;
}
