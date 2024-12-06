#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

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
    std::string vertexShader =
        "#version 330 core\n"
        "\n"
        "layout(location = 0) in vec4 position;"
        "\n"
        "void main(void)\n"
        "{\n"
        "gl_Position = position;\n"
        "}\n";
    //glsl ָ��Ƭ����ɫ��
    std::string fragmentShader =
        "#version 330 core\n"
        "\n"
        "layout(location = 0) out vec4 color;"          
        "\n"
        "void main(void)\n"
        "{\n"
        "color = vec4(1.0 , 0.8 , 0.3 , 1.0);\n"    //rgba
        "}\n";

    unsigned int shader = CreateShader(vertexShader, fragmentShader);
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