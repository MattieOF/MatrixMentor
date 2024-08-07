#pragma once

class RawModel
{
public:
	explicit RawModel(const std::vector<float>& vertices, const std::vector<float>& texCoords, const std::vector<uint32_t>& indices);
	~RawModel();

	void BindIndiciesBuffer(const std::vector<uint32_t>& indices);

	[[nodiscard]] FORCEINLINE uint32_t GetVAO()         const { return m_VAO; }
	[[nodiscard]] FORCEINLINE uint32_t GetIBO()         const { return m_IBO; }
	[[nodiscard]] FORCEINLINE uint32_t GetVertexCount() const { return m_VertexCount; }

private:
	void StoreDataInAttributeList(uint32_t index, const std::vector<float>& data, int32_t dataSize);

	static uint32_t CreateEmptyVAO();

	uint32_t m_VAO = 0, m_IBO = 0;
	std::vector<uint32_t> m_VBOs;
	uint32_t m_VertexCount;
};
