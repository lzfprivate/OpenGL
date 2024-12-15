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
#include <TestFramework/ClearColor.h>


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

    //ͬ���ֱ���
    glfwSwapInterval(1);

    if (GLEW_OK != glewInit())
        std::cout << "glew init error" << std::endl;
    {
        GLCall(glEnable(GL_BLEND));
        GLCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));

        CGLRenderer renderer;
        
        TestFramework::Test* testCurr = nullptr;
        test::CTestMenu* testMenu = new test::CTestMenu(testCurr);
        testCurr = testMenu;

        testMenu->registerTaskInstance<test::CClearColor>("ClearColor");

        ImGui::CreateContext(); 
        
        ImGui_ImplGlfwGL3_Init(window, true);
        ImGui::StyleColorsDark();

        while (!glfwWindowShouldClose(window))
        {
            /* Render here */
            GLCall(glClearColor(0.0f, 0.0f, 0.0f, 1.0f));
            renderer.Clear();

           
            //������֡
            ImGui_ImplGlfwGL3_NewFrame();
            if (testCurr)
            {
                testCurr->onUpdate(0.0f);
                testCurr->onRender();
                ImGui::Begin("Test");
                if (testCurr != testMenu && ImGui::Button("<-"))
                {
                    delete testCurr;
                    testCurr = testMenu;
                }
                testCurr->onImGuiRender();
                ImGui::End();
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