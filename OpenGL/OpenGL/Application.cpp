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
#include "GLTexture.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <imgui/imgui.h>
#include <imgui/imgui_impl_glfw_gl3.h>


int main(void)
{
    GLFWwindow* window;

    /* Initialize the library */
    if (!glfwInit())
        return -1;

    glfwInitHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwInitHint(GLFW_CONTEXT_VERSION_MINOR, 4);
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
        float postions[] =
        {
            100.0f,  100.0f,  0.0f,   0.0f,           //0
            200.0f,  100.0f,   1.0f,   0.0f,          //1
            200.0f,  200.0f,   1.0f,   1.0f,             //2
            100.0f,  200.0f,  0.0f,   1.0f            //3
        };


        //创建一个索引
        unsigned int indices[] = {
            0,1,2,          //postion数组组成的坐标代号
            0,2,3
        };
        GLCall(glEnable(GL_BLEND));
        GLCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));

        CGLVertexBuffer vb(postions, sizeof(postions));
        CGLIndexBuffer ib(indices, 6);
        CGLVertexBufferLayout layout;
        layout.Push<float>(2);
        layout.Push<float>(2);

        CGLVertexArray va;
        va.AddBuffer(vb, layout);
        //4:3 2.0 : 1.5
        glm::mat4 proj = glm::ortho(0.0f, 960.0f, 0.0f, 540.0f, -1.0f, 1.0f);
        //glm::vec4 vp(100.f, 100.f, 0.0f, 1.0f); 
        //相机(视图矩阵)，将所有的物体向右移动100个单位
        glm::mat4 view = glm::translate(glm::mat4(1.0), glm::vec3(-1.0f,0.0f,0.0f));
        

        //glm::vec4 result = proj * vp;

        glm::vec3 translation(200.0f, 200.0f, 0.0f);

        CGLShader shader("./Basic.shader");
        shader.Bind();
        //shader.SetUniform4f("u_Color", 0.8f, 0.3f, 0.5f, 1.0f);

        CGLRenderer renderer;

        ImGui::CreateContext(); 
        
        ImGui_ImplGlfwGL3_Init(window, true);
        ImGui::StyleColorsDark();


        CGLTexture texture("../Res/1.png");
        //CGLTexture texture("F:/GitProject/Opengl/OpenGL/Res/1.png");
        texture.Bind();
        shader.SetUniform1i("u_Texture", 0);

        float r = 0.0f;
        float step = 0.05f;

        //解绑
        shader.Unbind();
        va.Unbind();
        vb.Unbind();
        ib.Unbind();
        texture.Unbind();

        /* Loop until the user closes the window */
        while (!glfwWindowShouldClose(window))
        {
            /* Render here */
            renderer.Clear();

            //创建新帧
            ImGui_ImplGlfwGL3_NewFrame();

            glm::mat4 model = glm::translate(glm::mat4(1.0f), translation);
            //视图/模型矩阵
            glm::mat2 mvp = proj * view * model;

           

            //绘制数据，可以显示图形，在上面我们手动设置了顶点着色器和片段着色器
            
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
            texture.Bind();
            //shader.SetUniform1i("u_Texture", 0);
            shader.SetUniformMat4("u_MVP", mvp);
            ib.Bind();
            vb.Bind();
            va.Bind();
            renderer.Draw(shader, ib, va);

            {
                ImGui::SliderFloat3("Translation", &translation.x, 0.0f, 960.0f);            // Edit 1 float using a slider from 0.0f to 1.0f    
                ImGui::SliderFloat3("Translation", &translation.y, 0.0f, 540.0f);            // Edit 1 float using a slider from 0.0f to 1.0f    
                ImGui::SliderFloat3("Translation", &translation.z, 0.0f, 1.0f);            // Edit 1 float using a slider from 0.0f to 1.0f    
                ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
            }

            ImGui::Render();
            ImGui_ImplGlfwGL3_RenderDrawData(ImGui::GetDrawData());

            

            /* Swap front and back buffers */
            glfwSwapBuffers(window);

            /* Poll for and process events */
            glfwPollEvents();
        }
    }
    ImGui_ImplGlfwGL3_Shutdown();
    ImGui::DestroyContext();
    glfwTerminate();
    return 0;
}