#pragma once

class RawModel
{
public:
	explicit RawModel(const std::vector<float>& vertices);
	~RawModel();

private:
	void StoreDataInAttributeList(uint32_t index, const std::vector<float>& data, int32_t dataSize);

	static uint32_t CreateEmptyVAO();

	uint32_t m_VAO = 0;
	std::vector<uint32_t> m_VBOs;
	uint32_t VertexCount;
};
