#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <fstream>
#include <string>
#include <sstream>

#ifndef ASSERT(x)
#define ASSERT(x) if(!(x)) __debugbreak();
#endif // !ASSERT

#ifndef GLCall(x)
#define GLCall(x) GLClearError();\
x;\
ASSERT(GLLogCall(#x,__FILE__,__LINE__))

#endif // !ASSERT



struct ShaderSource
{
    std::string vertexSource;
    std::string fragmentSource;
};

//清除所有的错误
static void GLClearError()
{
    while (glGetError() != GL_NO_ERROR);
}

static void GLCheckError()
{
    while (GLenum num = glGetError())
        std::cout << "OPENGL ERROR : " << num << std::endl;
}

static bool GLLogCall(const char* function ,const char* file,int line)
{
    while (GLenum error = glGetError())
    {
        std::cout << "OPENGL ERROR : " << error << 
            "function" << function <<
            " line" << line <<
            " file" << file << std::endl;
        return false;
    }
    return true;
}

//从文件中读取着色器字符串
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
    float postions[] = {
        //添加了另一组三角形坐标轴的数据，数据冗余引出坐标缓冲区
        -0.5f, -0.5f,           //0
        -0.5f, 0.0f,            //1
        0.5f, 0.0f,             //2
        0.5f, -0.5f             //3
    };

    //创建一个索引
    unsigned int indices[] = {
        0,1,2,          //postion数组组成的坐标代号
        0,2,3
    };

    //创建索引缓冲区
    unsigned int ibo;       //index buffer object
    //创建一个缓冲区
    glGenBuffers(1, &ibo);
    //绑定缓冲区
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
    //缓冲区添加数据
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * sizeof(indices), indices, GL_STATIC_DRAW);


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

    //ShaderSource source = ParserShader("res/shader/Basic.shader");
    ShaderSource source = ParserShader("./Basic.shader");


    unsigned int shader = CreateShader(source.vertexSource, source.fragmentSource);
    glUseProgram(shader);

    
    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        /* Render here */
        glClear(GL_COLOR_BUFFER_BIT);
        //绘制数据，可以显示图形，在上面我们手动设置了顶点着色器和片段着色器

        //绘制两个三角形，成为一个矩形  
        //glDrawArrays(GL_TRIANGLES, 0, 6);

        //绘制前确保所有的错误己经被清除了
        //glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
        GLCall(glDrawElements(GL_TRIANGLES, 6, GL_INT, nullptr));
        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }
    glDeleteProgram(shader);
    glfwTerminate();
    return 0;
}