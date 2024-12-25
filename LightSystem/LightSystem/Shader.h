#pragma once
#include <string>
class Shader
{
public:
	Shader(const char* vertex, const char* fragment);
	~Shader();

	void use();

	void setVec3f(const std::string& name, float v0, float v1, float v2);
	void setMat4f(const std::string& name, float* valueList);

private:
	unsigned int m_nProgram;
};

