#include "mmpch.h"

#include "Core/Rendering/RawModel.h"

#include "glad/gl.h"

RawModel::RawModel(const std::vector<float>&    vertices, const std::vector<float>& texCoords,
                   const std::vector<uint32_t>& indices)
{
	m_VAO         = CreateEmptyVAO();
	m_VertexCount = static_cast<uint32_t>(indices.size());
	BindIndiciesBuffer(indices);
	StoreDataInAttributeList(0, vertices, 3);
	StoreDataInAttributeList(1, texCoords, 2);
	// Generate dummy normals
	std::vector normals(vertices.size(), glm::vec3(0.0f, 0.0f, 0.0f)); // TODO: Calculate normals
	StoreDataInAttributeList(2, normals);
	// A bit weird to have texCoords here, considering we have a TexturedModel class
	glBindVertexArray(0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0); // Unbind IBO after unbinding VAO, or it'll unbind the IBO from the VAO
}

RawModel::RawModel(const std::vector<glm::vec3>& vertices, const std::vector<glm::vec2>& texCoords,
	const std::vector<glm::vec3>& normals, const std::vector<uint32_t>& indices)
{
	m_VAO         = CreateEmptyVAO();
	m_VertexCount = static_cast<uint32_t>(indices.size());
	BindIndiciesBuffer(indices);
	StoreDataInAttributeList(0, vertices);
	StoreDataInAttributeList(1, texCoords);
	StoreDataInAttributeList(2, normals);
	// A bit weird to have texCoords here, considering we have a TexturedModel class
	glBindVertexArray(0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0); // Unbind IBO after unbinding VAO, or it'll unbind the IBO from the VAO
}

RawModel::~RawModel()
{
	if (m_VAO != 0)
		glDeleteVertexArrays(1, &m_VAO);
	if (m_IBO != 0)
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

void RawModel::BindVAO()
{
	MM_ASSERT_ERROR(m_VAO != 0, "RawModel::BindVAO called with invalid VAO!");
	
	glBindVertexArray(m_VAO);
	for (uint32_t i = 0; i < m_VertexAttributeCount; i++)
		glEnableVertexAttribArray(i);
}

void RawModel::UnbindVAO()
{
	glBindVertexArray(0);
	for (uint32_t i = 0; i < m_VertexAttributeCount; i++)
		glDisableVertexAttribArray(i);
}

void RawModel::StoreDataInAttributeList(uint32_t index, const std::vector<glm::vec3>& data)
{
	StoreDataInAttributeList(index, data.data(), sizeof(data[0]), data.size(), 3);
}

void RawModel::StoreDataInAttributeList(uint32_t index, const std::vector<glm::vec2>& data)
{
	StoreDataInAttributeList(index, data.data(), sizeof(data[0]), data.size(), 2);
}

void RawModel::StoreDataInAttributeList(const uint32_t index, const std::vector<float>& data, const int32_t dataStride)
{
	StoreDataInAttributeList(index, data.data(), sizeof(data[0]), data.size(), dataStride);
}

void RawModel::StoreDataInAttributeList(uint32_t index, const std::vector<uint32_t>& data, int32_t dataStride)
{
	StoreDataInAttributeList(index, data.data(), sizeof(data[0]), data.size(), dataStride, GL_UNSIGNED_INT);
}

void RawModel::StoreDataInAttributeList(const uint32_t index, const void* data, const size_t dataSize, const size_t dataCount,
                                        const int32_t  dataStride, const uint32_t dataType)
{
	MM_ASSERT_ERROR(dataType == GL_FLOAT || dataType == GL_UNSIGNED_INT, "Data type not supported!");
	
	uint32_t vboId;
	glGenBuffers(1, &vboId);
	m_VBOs.emplace_back(vboId);
	glBindBuffer(GL_ARRAY_BUFFER, vboId);
	glBufferData(GL_ARRAY_BUFFER, dataSize * dataCount, data, GL_STATIC_DRAW);
	glEnableVertexAttribArray(index);
	glVertexAttribPointer(index, dataStride, dataType, false, 0, nullptr);
	glDisableVertexAttribArray(index);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	m_VertexAttributeCount = std::max(m_VertexAttributeCount, index + 1);
}

uint32_t RawModel::CreateEmptyVAO()
{
	uint32_t vao;
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);
	return vao;
}
