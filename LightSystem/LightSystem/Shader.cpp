#include "Shader.h"
#include <fstream>
#include <iostream>
#include <sstream>

#include <glad.h>
#include <GLFW/glfw3.h>
Shader::Shader(const char* vertex, const char* fragment) : m_nProgram(-1)
{
	std::ifstream fsVertex, fsFragment;
	std::string strVertex, strFragment;
	
	try
	{
		fsVertex.open(vertex);
		fsFragment.open(fragment);
		std::stringstream ssVertex, ssFragment;
		ssVertex << fsVertex.rdbuf();
		ssFragment << fsFragment.rdbuf();
		strVertex = ssVertex.str();
		strFragment = ssFragment.str();
	}
	catch (const std::ifstream::failure e)
	{

	}
	
	const char* spVertex = strVertex.c_str();
	const char* spFragment = strFragment.c_str();

	unsigned int nShaderVertex = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(nShaderVertex, 1, &spVertex, nullptr);
	glCompileShader(nShaderVertex);

	int iRet = 0;
	char spLogMessage[512];
	glGetShaderiv(nShaderVertex, GL_COMPILE_STATUS, &iRet);
	if (!iRet)
	{
		glGetShaderInfoLog(nShaderVertex, 512, nullptr, spLogMessage);
		std::cout << "COMPILE VERTEX SHADER FAILED AT <" << vertex << "> ERROR MESSAGE:" << spLogMessage << std::endl;
	}


	unsigned int nShaderFrgment = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(nShaderFrgment, 1, &spFragment, nullptr);
	glCompileShader(nShaderFrgment);
	glGetShaderiv(nShaderFrgment, GL_COMPILE_STATUS, &iRet);
	if (!iRet)
	{
		glGetShaderInfoLog(nShaderFrgment, 512, nullptr, spLogMessage);
		std::cout << "COMPILE FRAGMENT SHADER FAILED AT <" << fragment << "> ERROR MESSAGE:" << spLogMessage << std::endl;
	}

	m_nProgram = glCreateProgram();
	glAttachShader(m_nProgram, nShaderVertex);
	glAttachShader(m_nProgram, nShaderFrgment);
	glLinkProgram(m_nProgram);
	glGetProgramiv(m_nProgram, GL_LINK_STATUS, &iRet);
	if (!iRet)
	{
		glGetProgramInfoLog(m_nProgram, 512, nullptr, spLogMessage);
		std::cout << "LINK PROGRAM FAILED: " << spLogMessage << std::endl;
	}

	glDeleteShader(nShaderVertex);
	glDeleteShader(nShaderFrgment);
}

Shader::~Shader()
{
	glDeleteProgram(m_nProgram);
}

void Shader::use()
{
	glUseProgram(m_nProgram);
}
void Shader::setValue1i(const std::string& name, int value)
{
	glUniform1i(glGetUniformLocation(m_nProgram, name.c_str()), value);
}
void Shader::setVec3f(const std::string& name, float v0, float v1, float v2)
{
	glUniform3f(glGetUniformLocation(m_nProgram, name.c_str()), v0, v1, v2);
}
void Shader::setMat4f(const std::string& name, float* valueList)
{
	glUniformMatrix4fv(glGetUniformLocation(m_nProgram, name.c_str()), 1, GL_FALSE, valueList);
}

void Shader::setMat4f(const std::string& name, glm::mat4 mat)
{
	glUniformMatrix4fv(glGetUniformLocation(m_nProgram, name.c_str()), 1, GL_FALSE, &mat[0][0]);
}


