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
    //��������������
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * sizeof(postions),postions,GL_STATIC_DRAW);
    
    //ȷ�����ݿ���
    glEnableVertexAttribArray(0);
    //֪ͨopengl���ʹ������
    // �ڶ����������������������Զ��ٸ�Ϊһ�� ����ǰΪ��ά���꣬������2
    //���һ������:��ǰֻ������һ�����ԣ����Ե�ǰ��ƫ����Ϊ0
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 2, 0);

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        /* Render here */
        glClear(GL_COLOR_BUFFER_BIT);
        //�������ݣ����в�������ʾ û��������ɫ��
        glDrawArrays(GL_TRIANGLES, 0, 3);       

        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}