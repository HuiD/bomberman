#ifndef __SHADERPROGRAM_H
#define __SHADERPROGRAM_H

#include <vector>
#include "shader.h"

enum class Attribs
{
	Vertex 	 = 0,
	Color 	 = 1,
	TexCoord = 2
};

class ShaderProgram
{
public:
	ShaderProgram();
	~ShaderProgram();

	bool addShader(const ShaderPtr& shader);
	bool addShaderFromSourceCode(Shader::ShaderType st, const std::string& sourceCode);
	bool addShaderFromFile(Shader::ShaderType st, const std::string& fileName);
	bool removeShader(const ShaderPtr& shader);

	bool create();
	bool link();
	bool bind();
	void bindAttribLocation(Attribs attrib, const char *name);
	std::string log();

private:
	uint m_programId;
	bool m_linked;
	std::vector<ShaderPtr> m_shaders;
};

#endif

