#pragma once

struct TextureSpecification
{

};

class Texture
{
public:
	explicit Texture(std::string_view filename, TextureSpecification spec = {});
	~Texture();

	void Activate(int slot = 0) const;
	void CleanUp();

	[[nodiscard]] FORCEINLINE int32_t  GetWidth()    const { return m_Width; }
	[[nodiscard]] FORCEINLINE int32_t  GetHeight()   const { return m_Height; }
	[[nodiscard]] FORCEINLINE int32_t  GetChannels() const { return m_Channels; }
	[[nodiscard]] FORCEINLINE uint32_t GetOpenGLID() const { return m_TextureID; }

private:
	int32_t m_Width = 0, m_Height = 0, m_Channels = 0;

	uint32_t m_TextureID = -1;
};
