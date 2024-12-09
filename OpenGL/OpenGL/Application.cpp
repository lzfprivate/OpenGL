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
#include "GLShader.h"



/// <summary>
/// 编译着色器
/// </summary>
/// <param name="vertexShader"></param>
/// <param name="type">着色器类型 </param>
/// <returns></returns>

/// <summary>
/// 
/// </summary>
/// <param name="vertexShader">顶点着色器</param>
/// <param name="fragmentShader">片段着色器</param>
/// <returns>标识符</returns>


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

    //同步分辨率
    glfwSwapInterval(1);

    if (GLEW_OK != glewInit())
        std::cout << "glew init error" << std::endl;
    {
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

        CGLVertexBuffer vb(postions, sizeof(postions));
        CGLIndexBuffer ib(indices, 6);
        CGLVertexBufferLayout vbl;
        vbl.Push<float>(2);

        CGLVertexArray va;
        va.AddBuffer(vb, vbl);

        CGLShader shader("./Basic.shader");
        shader.Bind();
        shader.SetUniform4f("u_Color", 0.8f, 0.3f, 0.5f, 1.0f);


        float r = 0.0f;
        float step = 0.05f;

        //解绑
        GLCall(glUseProgram(0));
        shader.Unbind();
        va.Unbind();
        vb.Unbind();
        ib.Unbind();

        /* Loop until the user closes the window */
        while (!glfwWindowShouldClose(window))
        {
            /* Render here */
            GLCall(glClear(GL_COLOR_BUFFER_BIT));
            //绘制数据，可以显示图形，在上面我们手动设置了顶点着色器和片段着色器

            //绘制两个三角形，成为一个矩形  
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

            shader.Bind();
            shader.SetUniform4f("u_Color", r, 0.2f, 0.3f, 1.0);
            ib.Bind();
            vb.Bind();
            va.Bind();
            //绘制前确保所有的错误己经被清除了
            //glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
            GLCall(glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr));
            /* Swap front and back buffers */
            glfwSwapBuffers(window);

            /* Poll for and process events */
            glfwPollEvents();
        }
    }
    glfwTerminate();
    return 0;
}