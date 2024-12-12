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
	//TODO:����������ʽ������
private:
	//��ȡuniform�ı�ʶ��
	int GetUniformLocation(const std::string& name);

	//����
	unsigned int CompileShader(unsigned int type,
		const std::string& source);
	//����
	unsigned int CreateShader(const std::string& vertexShader,
		const std::string& fragmentShader);
	//����
	ShaderSource ParserShader(const std::string& filepath);

};

