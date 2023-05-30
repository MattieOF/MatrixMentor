#pragma once

class RawModel
{
public:
	explicit RawModel(const std::vector<float>& vertices);
	~RawModel();

	[[nodiscard]] FORCEINLINE uint32_t GetVAO()         const { return m_VAO; }
	[[nodiscard]] FORCEINLINE uint32_t GetVertexCount() const { return m_VertexCount; }

private:
	void StoreDataInAttributeList(uint32_t index, const std::vector<float>& data, int32_t dataSize);

	static uint32_t CreateEmptyVAO();

	uint32_t m_VAO = 0;
	std::vector<uint32_t> m_VBOs;
	uint32_t m_VertexCount;
};
