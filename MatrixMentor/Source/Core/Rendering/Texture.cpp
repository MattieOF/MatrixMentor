#include "mmpch.h"
#include "Core/Rendering/Texture.h"

#include "Vendor/stb_image.h"
#include "glad/gl.h"

Texture::Texture(std::string_view filename, const TextureSpecification& spec)
{
	// Load texture from file using stb_image
	stbi_set_flip_vertically_on_load(spec.FlipVertically);
	uint8_t* data = stbi_load(filename.data(), &m_Width, &m_Height, &m_Channels, 4);

	// Error check texture loading
	if (data == nullptr)
	{
		MM_ERROR("Failed to load texture \"{0}\": {1}", filename, stbi_failure_reason());
		return; // TODO: Not properly indicating failure - best we do is 0 texture ID and 0 width/height
	}

	// Create OpenGL texture
	glGenTextures(1, &m_TextureID);
	glBindTexture(GL_TEXTURE_2D, m_TextureID);

	// Set texture parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, static_cast<GLint>(spec.Wrap));
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, static_cast<GLint>(spec.Wrap));
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, static_cast<GLint>(spec.MinFilter));
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, static_cast<GLint>(spec.MagFilter));
	
	// Set data
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, m_Width, m_Height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);

	// Generate mipmaps if needed
	if (spec.GenerateMipmaps)
		glGenerateMipmap(GL_TEXTURE_2D);

	stbi_image_free(data);
}

void Texture::CleanUp()
{
	MM_INFO("Cleaning up texture {0}", m_TextureID);
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
