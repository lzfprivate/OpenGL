#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>



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

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        /* Render here */
        glClear(GL_COLOR_BUFFER_BIT);
        //绘制数据，运行不会有显示 没有设置着色器
        glDrawArrays(GL_TRIANGLES, 0, 3);       

        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}