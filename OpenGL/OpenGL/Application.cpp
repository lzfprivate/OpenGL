#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <fstream>
#include <string>
#include <sstream>


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


    
    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(640, 480, "Hello World", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);

    if (GLEW_OK != glewInit())
        std::cout << "glew init error" << std::endl;

    std::cout << glGetString(GL_VERSION) << std::endl;

    //��֯��һ�����ݣ����������֪����ôȥʹ��
    float postions[6] = {
        -0.5f, -0.5f,
        0.0f, 0.0f,
        0.5f, -0.5f
    };

    unsigned int buffer;
    //����һ��������
    glGenBuffers(1, &buffer);
    //�󶨻�����
    glBindBuffer(GL_ARRAY_BUFFER, buffer);
    //�������������
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * sizeof(postions),postions,GL_STATIC_DRAW);
    
    //ȷ�����ݿ���
    glEnableVertexAttribArray(0);
    //֪ͨopengl���ʹ������
    // �ڶ����������������������Զ��ٸ�Ϊһ�� ����ǰΪ��ά���꣬������2
    //���һ������:��ǰֻ������һ�����ԣ����Ե�ǰ��ƫ����Ϊ0
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 2, 0);

    //glsl ָ��������ɫ��

    //ShaderSource source = ParserShader("res/shader/Basic.shader");
    ShaderSource source = ParserShader("./Basic.shader");
    std::cout << source.vertexSource << std::endl;
    std::cout << source.fragmentSource << std::endl;


    unsigned int shader = CreateShader(source.vertexSource, source.fragmentSource);
    glUseProgram(shader);

    
    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        /* Render here */
        glClear(GL_COLOR_BUFFER_BIT);
        //�������ݣ�������ʾͼ�Σ������������ֶ������˶�����ɫ����Ƭ����ɫ��
        glDrawArrays(GL_TRIANGLES, 0, 3);       

        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }
    glDeleteProgram(shader);
    glfwTerminate();
    return 0;
}