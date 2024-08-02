#pragma once

#include "glad/gl.h"

class ShaderProgram
{
public:
	ShaderProgram(std::string_view name);
	~ShaderProgram();

	static FORCEINLINE Ref<ShaderProgram> CreateShaderProgram(std::string_view name) { return CreateRef<ShaderProgram>(name); }
	int32_t AddStageFromSource(GLenum stage, std::string_view source);
	int32_t AddStageFromFile(GLenum stage, std::string_view source);
	int32_t CompileAndLink();
	
	// Binding functions
	FORCEINLINE void Bind() const { glUseProgram(m_ProgramID); }
	static FORCEINLINE void Unbind() { glUseProgram(0); }
	
	FORCEINLINE bool IsCompiled() const { return m_IsCompiled; }
	FORCEINLINE bool HasError() const { return m_HasError; }

	virtual void BindAttributes();
	void BindAttribute(int attribute, std::string_view variableName);

	void CleanUp();

	static FORCEINLINE bool IsValidShaderStage(GLenum value)
	{
		return value == GL_VERTEX_SHADER || value == GL_FRAGMENT_SHADER || value == GL_GEOMETRY_SHADER || value ==
			GL_TESS_EVALUATION_SHADER || value == GL_TESS_CONTROL_SHADER || value == GL_COMPUTE_SHADER;
	}
	static const char* GetShaderTypeString(GLenum type);

private:
	std::vector<int32_t> m_ShaderStages;
	std::vector<int32_t> m_Attributes;

	std::string m_Name = "Untitled Shader";
	int32_t m_ProgramID = -1;
	bool m_IsCompiled = false, m_HasError = false;
};
