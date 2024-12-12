#include "GLShader.h"
#include "GLCommondef.h"
#include <fstream>
#include <string>
#include <sstream>
#include <iostream>



CGLShader::CGLShader(const std::string& filepath)
	:m_nRendererID(-1),m_strFilePath(filepath)
{
    ShaderSource source = ParserShader(filepath);

    m_nRendererID = CreateShader(source.vertexSource, source.fragmentSource);

}

CGLShader::~CGLShader()
{
    GLCall(glDeleteProgram(m_nRendererID));
}

void CGLShader::Bind() const
{
    GLCall(glUseProgram(m_nRendererID));
}

void CGLShader::Unbind() const
{
    GLCall(glUseProgram(0));
}

void CGLShader::SetUniform4f(const std::string& name, float f0, float f1, float f2, float f3)
{
    GLCall(glUniform4f(GetUniformLocation(name), f0, f1, f2, f3));
}

void CGLShader::SetUniform1i(const std::string& name, int value)
{
    GLCall(glUniform1i(GetUniformLocation(name), value));
}

void CGLShader::SetUniformMat4(const std::string& name, const glm::mat4& matrix)
{
    GLCall(glUniformMatrix4fv(GetUniformLocation(name),1,GL_FALSE,&matrix[0][0]));
}



int CGLShader::GetUniformLocation(const std::string& name)
{
    if (m_umapLocation.find(name) != m_umapLocation.end())
        return m_umapLocation[name];

    GLCall(int location = glGetUniformLocation(m_nRendererID, name.c_str()));
    if (location == -1) std::cout << "bad location" << std::endl;
    m_umapLocation[name] = location;
   
	return location;
}
unsigned int CGLShader::CompileShader(unsigned int type,
    const std::string& source)
{
    unsigned int id = glCreateShader(type);
    const char* src = source.c_str();
    glShaderSource(id, 1, &src, nullptr);
    glCompileShader(id);

    int result;
    glGetShaderiv(id, GL_COMPILE_STATUS, &result);
    if (result == GL_FALSE)
    {
        int length;
        glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);
        char* message = (char*)alloca(sizeof(char) * length);
        glGetShaderInfoLog(id, length, &length, message);

        glDeleteShader(id);
        return 0;
    }
    return id;
}

unsigned int CGLShader::CreateShader(const std::string& vertexShader,
    const std::string& fragmentShader)
{
    unsigned int program = glCreateProgram();
    unsigned int vs = CompileShader(GL_VERTEX_SHADER, vertexShader);
    unsigned int fs = CompileShader(GL_FRAGMENT_SHADER, fragmentShader);

    glAttachShader(program, vs);
    glAttachShader(program, fs);

    glLinkProgram(program);
    glValidateProgram(program);

    glDeleteShader(vs);
    glDeleteShader(fs);

    return program;

}

//从文件中读取着色器字符串
ShaderSource CGLShader::ParserShader(const std::string& filepath)
{
    enum class ShaderType {
        NONE = -1,
        VERTEX = 0,
        FRAGMENT = 1
    };
    std::stringstream ss[2];
    std::ifstream stream(filepath);

    std::string line;

    ShaderType type = ShaderType::NONE;


    while (getline(stream, line))
    {
        if (line.find("#shader") != std::string::npos)
        {
            //找到#shader的字符串
            if (line.find("vertex") != std::string::npos)
            {
                //找到顶点着色器
                type = ShaderType::VERTEX;
            }
            else if (line.find("fragment") != std::string::npos)
            {
                //找到片段着色器
                type = ShaderType::FRAGMENT;
            }
        }
        else
        {
            ss[(int)type] << line << '\n';
        }
    }

    return { ss[0].str(),ss[1].str() };

}