#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

/// <summary>
/// 编译着色器
/// </summary>
/// <param name="vertexShader"></param>
/// <param name="type">着色器类型 </param>
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
/// <param name="vertexShader">顶点着色器</param>
/// <param name="fragmentShader">片段着色器</param>
/// <returns>标识符</returns>
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

    //组织了一组数据，但计算机不知道怎么去使用
    float postions[6] = {
        -0.5f, -0.5f,
        0.0f, 0.0f,
        0.5f, -0.5f
    };

    unsigned int buffer;
    //创建一个缓冲区
    glGenBuffers(1, &buffer);
    //绑定缓冲区
    glBindBuffer(GL_ARRAY_BUFFER, buffer);
    //缓冲区添加数据
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * sizeof(postions),postions,GL_STATIC_DRAW);
    
    //确保数据可用
    glEnableVertexAttribArray(0);
    //通知opengl如何使用数据
    // 第二个参数：缓冲区的数据以多少个为一组 ，当前为二维坐标，所以是2
    //最后一个参数:当前只有坐标一个属性，所以当前的偏移量为0
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 2, 0);

    //glsl 指定顶点着色器
    std::string vertexShader =
        "#version 330 core\n"
        "\n"
        "layout(location = 0) in vec4 position;"
        "\n"
        "void main(void)\n"
        "{\n"
        "gl_Position = position;\n"
        "}\n";
    //glsl 指定片段着色器
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
        //绘制数据，可以显示图形，在上面我们手动设置了顶点着色器和片段着色器
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