#ifndef __SHADER_H
#define __SHADER_H

#include <memory>

class Shader
{
public:
	enum ShaderType
	{
		Vertex,
		Fragment
	};

	Shader(ShaderType shaderType);
	~Shader();

	bool compile(const std::string& sourceCode);
	std::string log();
	uint id() const { return m_id; }

private:
	uint m_id;
};

typedef std::shared_ptr<Shader> ShaderPtr;

#endif

