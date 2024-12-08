#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <fstream>
#include <string>
#include <sstream>
#include "GLRenderer.h"
#include "GLVertexBuffer.h"
#include "GLIndexBuffer.h"
#include "GLVertexArray.h"

struct ShaderSource
{
    std::string vertexSource;
    std::string fragmentSource;
};
//���ļ��ж�ȡ��ɫ���ַ���
static ShaderSource ParserShader(const std::string& filepath)
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


    while (getline(stream,line))
    {
        if (line.find("#shader") != std::string::npos)
        {
            //�ҵ�#shader���ַ���
            if (line.find("vertex") != std::string::npos)
            {
                //�ҵ�������ɫ��
                type = ShaderType::VERTEX;
            }
            else if (line.find("fragment") != std::string::npos)
            {
                //�ҵ�Ƭ����ɫ��
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

/// <summary>
/// ������ɫ��
/// </summary>
/// <param name="vertexShader"></param>
/// <param name="type">��ɫ������ </param>
/// <returns></returns>
static int CompileShader(unsigned int type,
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
/// <summary>
/// 
/// </summary>
/// <param name="vertexShader">������ɫ��</param>
/// <param name="fragmentShader">Ƭ����ɫ��</param>
/// <returns>��ʶ��</returns>
static unsigned int CreateShader(const std::string& vertexShader, 
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

int main(void)
{
    GLFWwindow* window;

    /* Initialize the library */
    if (!glfwInit())
        return -1;

    glfwInitHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwInitHint(GLFW_CONTEXT_VERSION_MINOR, 5);
    glfwInitHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);



    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(640, 480, "Hello World", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }
    std::cout << glfwGetVersionString() << std::endl;



    /* Make the window's context current */
    glfwMakeContextCurrent(window);

    //ͬ���ֱ���
    glfwSwapInterval(1);

    if (GLEW_OK != glewInit())
        std::cout << "glew init error" << std::endl;
    {
        //��֯��һ�����ݣ����������֪����ôȥʹ��
        float postions[] = {
            //�������һ������������������ݣ����������������껺����
            -0.5f, -0.5f,           //0
            -0.5f, 0.0f,            //1
            0.5f, 0.0f,             //2
            0.5f, -0.5f             //3
        };

        //����һ������
        unsigned int indices[] = {
            0,1,2,          //postion������ɵ��������
            0,2,3
        };

        CGLVertexBuffer vb(postions, sizeof(postions));
        CGLIndexBuffer ib(indices, 6);
        CGLVertexBufferLayout vbl;
        vbl.Push<float>(2);

        CGLVertexArray va;
        va.AddBuffer(vb, vbl);

        //glsl ָ��������ɫ��

        //ShaderSource source = ParserShader("res/shader/Basic.shader");
        ShaderSource source = ParserShader("./Basic.shader");

        unsigned int shader = CreateShader(source.vertexSource, source.fragmentSource);
        GLCall((glUseProgram(shader)));
        GLCall(int location = glGetUniformLocation(shader, "u_Color"));
        ASSERT(location != -1);
        //�Ӵ���������ɫ������ɫ
        GLCall(glUniform4f(location, 0.8f, 0.2f, 0.3f, 1.0));

        float r = 0.0f;
        float step = 0.05f;

        //���
        GLCall(glUseProgram(0));
        va.Unbind();
        vb.Unbind();
        ib.Unbind();

        /* Loop until the user closes the window */
        while (!glfwWindowShouldClose(window))
        {
            /* Render here */
            GLCall(glClear(GL_COLOR_BUFFER_BIT));
            //�������ݣ�������ʾͼ�Σ������������ֶ������˶�����ɫ����Ƭ����ɫ��

            //�������������Σ���Ϊһ������  
            //glDrawArrays(GL_TRIANGLES, 0, 6);
            if (r > 1.0f)
            {
                step = -0.05f;
            }
            else if (r < 0.0f)
            {
                step = 0.05f;
            }
            r += step;

            GLCall(glUseProgram(shader));
            GLCall(glUniform4f(location, r, 0.2f, 0.3f, 1.0));

            ib.Bind();
            vb.Bind();
            va.Bind();
            //����ǰȷ�����еĴ��󼺾��������
            //glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
            GLCall(glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr));
            /* Swap front and back buffers */
            glfwSwapBuffers(window);

            /* Poll for and process events */
            glfwPollEvents();
        }
        glDeleteProgram(shader);
    }
    glfwTerminate();
    return 0;
}