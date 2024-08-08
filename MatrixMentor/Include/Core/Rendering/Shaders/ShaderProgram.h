#pragma once

#include "glad/gl.h"

class ShaderProgram
{
public:
	ShaderProgram(std::string_view name);
	virtual ~ShaderProgram();
	ShaderProgram(ShaderProgram&& other) noexcept = delete; // Disallow move constructor
	ShaderProgram(const ShaderProgram& other) = delete; // Disallow copy constructor

	static FORCEINLINE Ref<ShaderProgram> CreateShaderProgram(std::string_view name) { return CreateRef<ShaderProgram>(name); }
	int32_t AddStageFromSource(GLenum stage, std::string_view source);
	int32_t AddStageFromFile(GLenum stage, std::string_view source);
	int32_t LinkProgram();
	
	// Binding functions
	void Bind() const;
	static FORCEINLINE void Unbind() { glUseProgram(0); }

    // Uniform functions
    int GetUniformLocation(std::string_view uniformName);
    [[nodiscard]] int GetUniformLocation(std::string_view uniformName) const;
    virtual void GetUniformLocations();

    void SetUniform1b(std::string_view uniformName, bool value) const;
    void SetUniform1i(std::string_view uniformName, int value) const;
    void SetUniform1f(std::string_view uniformName, float value) const;
    void SetUniform2f(std::string_view uniformName, float x, float y) const;
	void SetUniformVec2(std::string_view uniformName, const glm::vec2& vec) const;
    void SetUniform3f(std::string_view uniformName, float x, float y, float z) const;
	void SetUniformVec3(std::string_view uniformName, const glm::vec3& vec) const;
    void SetUniform4f(std::string_view uniformName, float x, float y, float z, float w) const;
	void SetUniformVec4(std::string_view uniformName, const glm::vec4& vec) const;
	void SetUniformMatrix3f(std::string_view uniformName, const glm::mat3& vec) const;
    void SetUniformMatrix4f(std::string_view uniformName, const glm::mat4& matrix) const;

	FORCEINLINE bool IsComplete() const { return m_IsComplete; }
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
	std::unordered_map<std::string, int32_t> m_UniformLocations;

	std::string m_Name = "Untitled Shader";
	int32_t m_ProgramID = -1;
	bool m_IsComplete = false, m_HasError = false;
};
