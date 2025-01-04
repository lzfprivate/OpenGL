#pragma once
#include <string>
#include <glm.hpp>
class Shader
{
public:
	Shader(const char* vertex, const char* fragment);
	~Shader();

	void use();

	void setValue1i(const std::string& name, int value);

	void setVec3f(const std::string& name, float v0, float v1, float v2);
	void setMat4f(const std::string& name, float* valueList);
	void setMat4f(const std::string& name, glm::mat4 mat);

private:
	unsigned int m_nProgram;
};

