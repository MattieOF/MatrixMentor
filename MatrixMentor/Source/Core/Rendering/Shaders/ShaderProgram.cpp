#include "mmpch.h"

#include "Core/Rendering/Shaders/ShaderProgram.h"

ShaderProgram::ShaderProgram(std::string_view name, std::string_view vertexSrc, std::string_view fragmentSrc)
	: m_Name(name)
{
	// Load shaders
	int32_t vertex   = LoadShader(GL_VERTEX_SHADER, vertexSrc);
	if (vertex == -1) return;
	int32_t fragment = LoadShader(GL_FRAGMENT_SHADER, fragmentSrc);
	if (fragment == -1) return;

	// Create the program and attach and link the shaders
	m_ProgramID = glCreateProgram();
	glAttachShader(m_ProgramID, vertex);
	glAttachShader(m_ProgramID, fragment);
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
		glDeleteShader(vertex);
		glDeleteShader(fragment);
		glDeleteProgram(m_ProgramID);

		return;
	}

	MM_INFO("Created shader program {0}!", m_Name);

	// Clean up by detaching
	glDetachShader(m_ProgramID, vertex);
	glDetachShader(m_ProgramID, fragment);
}

ShaderProgram::~ShaderProgram()
{
	CleanUp();
}

Ref<ShaderProgram> ShaderProgram::LoadShaderFromFiles(std::string_view name, std::string_view vertexPath, std::string_view fragmentPath)
{
	// Open source files and read to string stream
	std::ifstream vertexFile(vertexPath.data());
	if (!vertexFile.good())
	{
		MM_ERROR("Failed to open vertex shader \"{0}\"", vertexPath);
		return nullptr;
	}
	std::stringstream vertexBuffer;
	vertexBuffer << vertexFile.rdbuf();

	std::ifstream fragmentFile(fragmentPath.data());
	if (!fragmentFile.good())
	{
		MM_ERROR("Failed to open fragment shader \"{0}\"", fragmentPath);
		return nullptr;
	}
	std::stringstream fragmentBuffer;
	fragmentBuffer << fragmentFile.rdbuf();

	// Create shader
	Ref<ShaderProgram> program = CreateRef<ShaderProgram>(name, vertexBuffer.str(), fragmentBuffer.str());

	// Clean up files
	vertexFile.close();
	fragmentFile.close();

	// Finally, return result
	return program;
}

void ShaderProgram::BindAttribute(int attribute, std::string_view variableName)
{
	glBindAttribLocation(m_ProgramID, attribute, variableName.data());
}

void ShaderProgram::CleanUp()
{
	// TODO: leak, gotta delete shaders
	// add all shaders to a vector
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
	default:
		return fmt::format("Unknown Shader Type ({0})", type).c_str();
	}
}

int32_t ShaderProgram::LoadShader(GLenum type, std::string_view source)
{
	int32_t shaderID = glCreateShader(type);
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
		MM_ERROR_NO_NEWLINE("In shader {0}, failed to compile {1}: {2}", m_Name, GetShaderTypeString(type), std::string_view(&message[0], logLength));
		glDeleteShader(shaderID);
		return -1;
	}

	return shaderID;
}
