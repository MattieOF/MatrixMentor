#pragma once

enum class WrapMode
{
	Repeat = 0x2901, // GL_REPEAT
	MirroredRepeat = 0x8370, // GL_MIRRORED_REPEAT
	ClampToEdge = 0x812F, // GL_CLAMP_TO_EDGE
	ClampToBorder = 0x812D, // GL_CLAMP_TO_BORDER
};

enum class FilterMode
{
	Nearest = 0x2600, // GL_NEAREST
	Linear = 0x2601, // GL_LINEAR
};

struct TextureSpecification
{
	bool FlipVertically = true;
	bool GenerateMipmaps = true;
	WrapMode Wrap = WrapMode::Repeat;
	FilterMode MinFilter = FilterMode::Linear;
	FilterMode MagFilter = FilterMode::Linear;
};

class Texture
{
public:
	explicit Texture(std::string_view filename, const TextureSpecification& spec = {});
	~Texture();

	void Activate(int slot = 0) const;
	void CleanUp();

	[[nodiscard]] FORCEINLINE int32_t  GetWidth() const { return m_Width; }
	[[nodiscard]] FORCEINLINE int32_t  GetHeight() const { return m_Height; }
	[[nodiscard]] FORCEINLINE int32_t  GetChannels() const { return m_Channels; }
	[[nodiscard]] FORCEINLINE uint32_t GetOpenGLID() const { return m_TextureID; }

private:
	int32_t m_Width = 0, m_Height = 0, m_Channels = 0;

	uint32_t m_TextureID = -1;
};
