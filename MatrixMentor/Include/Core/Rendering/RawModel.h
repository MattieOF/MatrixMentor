#pragma once

class RawModel
{
public:
	explicit RawModel(const std::vector<float>&    vertices, const std::vector<float>& texCoords,
	                  const std::vector<uint32_t>& indices);
	explicit RawModel(const std::vector<glm::vec3>& vertices, const std::vector<glm::vec2>& texCoords,
	                  const std::vector<glm::vec3>& normals, const std::vector<uint32_t>& indices);
	~RawModel();

	void BindIndiciesBuffer(const std::vector<uint32_t>& indices);

	void BindVAO();
	void UnbindVAO();

	[[nodiscard]] FORCEINLINE uint32_t GetVAO() const { return m_VAO; }
	[[nodiscard]] FORCEINLINE uint32_t GetIBO() const { return m_IBO; }
	[[nodiscard]] FORCEINLINE uint32_t GetVertexCount() const { return m_VertexCount; }

private:
	void StoreDataInAttributeList(uint32_t index, const std::vector<glm::vec3>& data);
	void StoreDataInAttributeList(uint32_t index, const std::vector<glm::vec2>& data);
	void StoreDataInAttributeList(uint32_t index, const std::vector<float>& data, int32_t dataStride);
	void StoreDataInAttributeList(uint32_t index, const std::vector<uint32_t>& data, int32_t dataStride);
	void StoreDataInAttributeList(uint32_t index, const void* data, size_t dataSize, size_t dataCount, int32_t dataStride, uint32_t dataType = 0x1406); // 0x1406 = GL_FLOAT

	static uint32_t CreateEmptyVAO();

	uint32_t              m_VAO = 0, m_IBO = 0;
	std::vector<uint32_t> m_VBOs;
	uint32_t              m_VertexCount;
	uint32_t              m_VertexAttributeCount = 0;
};
