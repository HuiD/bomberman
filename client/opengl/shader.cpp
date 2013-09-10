#include "shader.h"
#include "glinc.h"

#include <vector>

Shader::Shader(ShaderType type)
{
	switch (type) {
		case Vertex:
			m_id = glCreateShader(GL_VERTEX_SHADER);
			break;
		case Fragment:
			m_id = glCreateShader(GL_FRAGMENT_SHADER);
			break;
	}
}

Shader::~Shader()
{
	glDeleteShader(m_id);
}

bool Shader::compile(const std::string& sourceCode)
{
#ifndef OPENGL_ES
	static const char *qualifierDefinitions =
		"#define lowp\n"
		"#define mediump\n"
		"#define highp\n";
#else
	static const char *qualifierDefinitions =
		"#ifndef GL_FRAGMENT_PRECISION_HIGH\n"
		"#define highp mediump\n"
		"#endif\n"
		"precision highp float;\n";
#endif

	std::string code = qualifierDefinitions;
	code.append(sourceCode);

	GLint len = code.length();
	const char *src = code.c_str();

	glShaderSource(m_id, 1, (const GLchar **)&src, &len);
	glCompileShader(m_id);

	GLint status;
	glGetShaderiv(m_id, GL_COMPILE_STATUS, &status);

	return status == GL_TRUE;
}

std::string Shader::log()
{
	int infoLogLength = 0;
	std::string infoLog;

	glGetShaderiv(m_id, GL_INFO_LOG_LENGTH, &infoLogLength);
	if (infoLogLength > 1) {
		std::vector<char> buf(infoLogLength);
		glGetShaderInfoLog(m_id, infoLogLength - 1, NULL, &buf[0]);
		infoLog = &buf[0];
	}

	return infoLog;
}

