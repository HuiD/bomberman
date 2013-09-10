#include "shaderprogram.h"
#include "glinc.h"

#include <algorithm>

ShaderProgram::ShaderProgram() :
	m_programId(0),
	m_linked(false)
{

}

ShaderProgram::~ShaderProgram()
{
	m_shaders.clear();
	glDeleteProgram(m_programId);
}

bool ShaderProgram::addShader(const ShaderPtr& shader)
{
	if (!shader || !shader->id())
		return false;

	glAttachShader(m_programId, shader->id());
	m_shaders.push_back(shader);
	return true;
}

bool ShaderProgram::addShaderFromSourceCode(Shader::ShaderType st, const std::string& sourceCode)
{
	ShaderPtr shader(new Shader(st));
	if (!shader->compile(sourceCode))
		return false;

	glAttachShader(m_programId, shader->id());
	m_shaders.push_back(shader);
	return true;
}

bool ShaderProgram::addShaderFromFile(Shader::ShaderType st, const std::string& fileName)
{
	FILE *fp = fopen(fileName.c_str(), "r");
	if (!fp)
		return false;

	fseek(fp, 0L, SEEK_END);
	size_t len = ftell(fp);
	fseek(fp, 0L, SEEK_SET);

	std::vector<char> buf(len);
	if (fread(&buf[0], len, 1, fp) != len)
		return false;

	fclose(fp);

	ShaderPtr shader(new Shader(st));
	if (!shader->compile(&buf[0]))
		return false;

	glAttachShader(m_programId, shader->id());
	m_shaders.push_back(shader);
	return true;
}

bool ShaderProgram::removeShader(const ShaderPtr& shader)
{
	auto it = std::find(m_shaders.begin(), m_shaders.end(), shader);
	if (it == m_shaders.end())
		return false;

	glDetachShader(m_programId, shader->id());
	m_shaders.erase(it);
	m_linked = false;
	return true;
}

bool ShaderProgram::create()
{
	return !!(m_programId = glCreateProgram());
}

bool ShaderProgram::link()
{
	if (m_linked)
		return true;

	glLinkProgram(m_programId);

	int status;
	glGetProgramiv(m_programId, GL_LINK_STATUS, &status);
	m_linked = status != GL_FALSE;

	return m_linked;
}

bool ShaderProgram::bind()
{
	if (!m_linked && !link())
		return false;

	glUseProgram(m_programId);
	return true;
}

void ShaderProgram::bindAttribLocation(Attribs attrib, const char *name)
{
	glBindAttribLocation(m_programId, (int)attrib, name);
	glEnableVertexAttribArray((int)attrib);
}

std::string ShaderProgram::log()
{
	std::string infoLog;
	int infoLogLength;

	glGetProgramiv(m_programId, GL_INFO_LOG_LENGTH, &infoLogLength);
	if (infoLogLength > 1) {
		std::vector<char> buf(infoLogLength);
		glGetShaderInfoLog(m_programId, infoLogLength - 1, NULL, &buf[0]);
		infoLog = &buf[0];
	}

	return infoLog;
}

