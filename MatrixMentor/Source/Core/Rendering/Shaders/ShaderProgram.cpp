#include "mmpch.h"

#include "Core/Rendering/Shaders/ShaderProgram.h"

ShaderProgram::ShaderProgram(std::string_view name)
	: m_Name(name)
{
	m_ProgramID = glCreateProgram();
}

ShaderProgram::~ShaderProgram()
{
	CleanUp();
}

int32_t ShaderProgram::AddStageFromSource(GLenum stage, std::string_view source)
{
	if (m_IsCompiled)
	{
		MM_ERROR("In shader {0}, attempting to add a stage to a compiled shader!", m_Name);
		return -1;
	}

	if (!IsValidShaderStage(stage))
	{
		MM_ERROR("ShaderProgram::AddStage of shader \"{0}\" called with invalid stage enum: {1}.\nShould be one of: GL_VERTEX_SHADER, GL_FRAGMENT_SHADER, GL_TESS_EVALUATION_SHADER, GL_TESS_CONTROL_SHADER, GL_COMPUTE_SHADER", m_Name, stage);
		return -1;
	}

	for (int32_t attrib : m_Attributes)
		glEnableVertexAttribArray(attrib);

	int32_t shaderID = glCreateShader(stage);
	const auto length = static_cast<int32_t>(source.length());
	const char* data = source.data();
	glShaderSource(shaderID, 1, &data, &length);
	glCompileShader(shaderID);

	GLint compiled;
	glGetShaderiv(shaderID, GL_COMPILE_STATUS, &compiled);
	if (compiled != GL_TRUE)
	{
		GLsizei logLength = 0;
		static GLchar message[1024];
		glGetShaderInfoLog(shaderID, 1024, &logLength, message);
		MM_ERROR_NO_NEWLINE("In shader {0}, failed to compile {1}: {2}", m_Name, GetShaderTypeString(stage), std::string_view(&message[0], logLength));
		glDeleteShader(shaderID);
		return -1;
	}

	m_ShaderStages.emplace_back(shaderID);

	return shaderID;
}

int32_t ShaderProgram::AddStageFromFile(GLenum stage, std::string_view source)
{
	// Open source file and read to string stream
	std::ifstream sourceFile(source.data());
	if (!sourceFile.good())
	{
		MM_ERROR("Failed to open shader source \"{0}\"", source);
		return -1;
	}
	std::stringstream buffer;
	buffer << sourceFile.rdbuf();

	// Call into add stage from source
	const int32_t result = AddStageFromSource(stage, buffer.str());

	// Clean up
	sourceFile.close();

	return result;
}

int32_t ShaderProgram::CompileAndLink()
{
	for (int32_t attrib : m_Attributes)
		glEnableVertexAttribArray(attrib);

	// Create the program and attach and link all shaders
	for (const int32_t shaderID : m_ShaderStages)
		glAttachShader(m_ProgramID, shaderID);
	glLinkProgram(m_ProgramID);
	glValidateProgram(m_ProgramID);
	
	// Check we linked successfully
	int32_t success = 0;
	glGetProgramiv(m_ProgramID, GL_LINK_STATUS, &success);
	if (success == GL_FALSE)
	{
		// Get error log and print it
		GLint logLength = 0;
		glGetProgramiv(m_ProgramID, GL_INFO_LOG_LENGTH, &logLength);
		std::vector<char> infoLog(logLength);
		glGetProgramInfoLog(m_ProgramID, logLength, &logLength, infoLog.data());
		MM_ERROR("Failed to link shader {0}: {1}", m_Name, infoLog.data());

		// Clean up
		for (const int32_t shaderID : m_ShaderStages)
		{
			glDetachShader(m_ProgramID, shaderID);
			glDeleteShader(shaderID);
		}

		return -1;
	}

	MM_INFO("Created shader program {0}!", m_Name);

	// Clean up by detaching
	for (const int32_t shaderID : m_ShaderStages)
		glDetachShader(m_ProgramID, shaderID);

	m_IsCompiled = true;
	
	return m_ProgramID;
}

void ShaderProgram::BindAttribute(int attribute, std::string_view variableName)
{
	glBindAttribLocation(m_ProgramID, attribute, variableName.data());
	m_Attributes.emplace_back(attribute);
}

void ShaderProgram::CleanUp()
{
	for (const int32_t shaderID : m_ShaderStages)
		glDeleteShader(shaderID);
	glDeleteProgram(m_ProgramID);
}

const char* ShaderProgram::GetShaderTypeString(GLenum type)
{
	switch (type)
	{
	case GL_VERTEX_SHADER:
		return "Vertex Shader";
	case GL_FRAGMENT_SHADER:
		return "Fragment Shader";
	case GL_GEOMETRY_SHADER:
		return "Geometry Shader";
	case GL_TESS_CONTROL_SHADER:
		return "Tessellation Control Shader";
	case GL_TESS_EVALUATION_SHADER:
		return "Tessellation Evaluation Shader";
	case GL_COMPUTE_SHADER:
		return "Compute Shader";
	default:
		return fmt::format("Unknown Shader Type ({0})", type).c_str();
	}
}
