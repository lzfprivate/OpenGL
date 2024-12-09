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
/// ������ɫ��
/// </summary>
/// <param name="vertexShader"></param>
/// <param name="type">��ɫ������ </param>
/// <returns></returns>

/// <summary>
/// 
/// </summary>
/// <param name="vertexShader">������ɫ��</param>
/// <param name="fragmentShader">Ƭ����ɫ��</param>
/// <returns>��ʶ��</returns>


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

        CGLShader shader("./Basic.shader");
        shader.Bind();
        shader.SetUniform4f("u_Color", 0.8f, 0.3f, 0.5f, 1.0f);


        float r = 0.0f;
        float step = 0.05f;

        //���
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

            shader.Bind();
            shader.SetUniform4f("u_Color", r, 0.2f, 0.3f, 1.0);
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
    }
    glfwTerminate();
    return 0;
}