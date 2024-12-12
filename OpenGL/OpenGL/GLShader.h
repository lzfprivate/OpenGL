#pragma once
#include <string>
#include <unordered_map>
#include <glm/glm.hpp>
struct ShaderSource
{
	std::string vertexSource;
	std::string fragmentSource;
};

class CGLShader
{
private:
	unsigned int m_nRendererID;
	std::string m_strFilePath;
	std::unordered_map<std::string, int> m_umapLocation;

public:
	CGLShader(const std::string& filepath);
	~CGLShader();
	
	void Bind() const;
	void Unbind() const;

	//set uniform
	void SetUniform4f(const std::string& name, float f0, float f1, float f2, float f3);
	void SetUniform1i(const std::string& name, int value);

	void SetUniformMat4(const std::string& name, const glm::mat4& matrix);
	//TODO:设置其他格式的内容
private:
	//获取uniform的标识符
	int GetUniformLocation(const std::string& name);

	//编译
	unsigned int CompileShader(unsigned int type,
		const std::string& source);
	//创建
	unsigned int CreateShader(const std::string& vertexShader,
		const std::string& fragmentShader);
	//解析
	ShaderSource ParserShader(const std::string& filepath);

};

