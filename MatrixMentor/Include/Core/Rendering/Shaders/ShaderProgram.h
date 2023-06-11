#pragma once
#include "glad/gl.h"

class ShaderProgram
{
public:
	ShaderProgram(std::string_view name, std::string_view vertexSrc, std::string_view fragmentSrc);
	~ShaderProgram();

	static Ref<ShaderProgram> LoadShaderFromFiles(std::string_view name, std::string_view vertexPath, std::string_view fragmentPath);

	// Binding functions
	FORCEINLINE void Bind() const { glUseProgram(m_ProgramID); }
	static FORCEINLINE void Unbind() { glUseProgram(0); }

	void BindAttribute(int attribute, std::string_view variableName);

	void CleanUp();

	static const char* GetShaderTypeString(GLenum type);

private:
	int32_t LoadShader(GLenum type, std::string_view source);

	std::string m_Name = "Untitled Shader";
	int32_t m_ProgramID = -1;
};
