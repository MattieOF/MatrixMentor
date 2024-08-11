#include "mmpch.h"
#include "Core/Rendering/Texture.h"

#include "Vendor/stb_image.h"
#include "glad/gl.h"

Texture::Texture(std::string_view filename, TextureSpecification spec)
{
	// Load texture from file using stb_image
	uint8_t* data = stbi_load(filename.data(), &m_Width, &m_Height, &m_Channels, 4);

	// Error check texture loading
	if (data == nullptr)
	{
		// Failed to load texture
		MM_ERROR("Failed to load texture \"{0}\": {1}", filename, stbi_failure_reason());
		return;
	}

	// Create OpenGL texture
	glGenTextures(1, &m_TextureID);
	glBindTexture(GL_TEXTURE_2D, m_TextureID);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, m_Width, m_Height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
	glGenerateMipmap(GL_TEXTURE_2D);

	stbi_image_free(data);
}

void Texture::CleanUp()
{
	glDeleteTextures(1, &m_TextureID);
	m_TextureID = 0;
}

Texture::~Texture()
{
	CleanUp();
}

void Texture::Activate(int slot) const
{
	MM_ASSERT_ERROR(m_TextureID != 0, "Texture activated when not initialized");
	
	glActiveTexture(GL_TEXTURE0 + slot);
	glBindTexture(GL_TEXTURE_2D, m_TextureID);
}
