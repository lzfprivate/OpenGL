#include <glad.h>
#include <GLFW/glfw3.h>
#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>
#include <iostream>
#include "Shader.h"
#include "Camera.h"



void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void keyboard_callback(GLFWwindow* window);
void mouse_callback(GLFWwindow* window, double xPos, double yPos);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);

const unsigned int SCREEN_WIDTH = 800;
const unsigned int SCREEN_HEIGHT = 600;

float g_pos[] = { 
	 -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
	 0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
	 0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
	 0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
	-0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
	-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,

	-0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
	 0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
	 0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
	 0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
	-0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
	-0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,

	-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
	-0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
	-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
	-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
	-0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
	-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,

	 0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
	 0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
	 0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
	 0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
	 0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
	 0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,

	-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
	 0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
	 0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
	 0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
	-0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
	-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,

	-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
	 0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
	 0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
	 0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
	-0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
	-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f
};

unsigned int g_index[] = {1};


glm::vec3 lightPos(1.2f, 1.0f, 2.0f);

Camera g_camera;

//键盘操作相关参数		
float g_fDeltaTime = 0.0f;

//鼠标操作相关参数
bool g_bFirstClick = true;		//首次点击鼠标
float g_fLastX = 0;				//上次操作的鼠标x轴	
float g_fLastY = 0;				//上次操作的鼠标y轴
float g_lastFrame = 0;			//上次更新的帧数



int main()
{
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	GLFWwindow* window = glfwCreateWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "LightSystem", nullptr, nullptr);

	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
	glfwSetCursorPosCallback(window, mouse_callback);
	glfwSetScrollCallback(window, scroll_callback);
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to load glad plugin" << std::endl;
		return -2;
	}

	glEnable(GL_DEPTH_TEST);

	unsigned int nVao, nVbo;
	
	glGenVertexArrays(1, &nVao);
	
	glBindVertexArray(nVao);

	glGenBuffers(1, &nVbo);
	glBindBuffer(GL_ARRAY_BUFFER, nVbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(g_pos), g_pos, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 6, (void*)0);
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 6, (void*)0);
	glEnableVertexAttribArray(1);

	Shader shaderObject("objectVertex.shader","objectFragment.shader");
	shaderObject.use();
	
	unsigned int nVaoLight;
	glGenVertexArrays(1, &nVaoLight);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 6, (void*)0);
	glEnableVertexAttribArray(0);

	Shader shaderLight("lightVertex.shader", "lightFragment.shader");
	shaderLight.use();

	while (!glfwWindowShouldClose(window))
	{
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		keyboard_callback(window);

		shaderObject.use();

		glm::mat4 projection = glm::perspective(glm::radians(g_camera.mouseDegree()),
			(float)(SCREEN_WIDTH / SCREEN_HEIGHT), 0.1f, 100.0f);
		glm::mat3 view = glm::mat4(1.0f);

		glm::mat4 model = glm::mat4(1.0);
		shaderObject.setMat4f("model", glm::value_ptr(model));
		shaderObject.setMat4f("view", glm::value_ptr(view));
		shaderObject.setMat4f("projection", glm::value_ptr(projection));
		shaderObject.setVec3f("objectColor", 1.0f, 0.5f, 0.31f);
		shaderObject.setVec3f("lightColor", 1.0f, 1.0f, 1.0f);
		shaderObject.setVec3f("lightColor", 1.0f, 1.0f, 1.0f);

		glBindVertexArray(nVao);
		glDrawArrays(GL_TRIANGLES, 0, 36);
	

		model = glm::translate(model, lightPos);
		model = glm::scale(model, glm::vec3(1.0, 1.0, 0.2f));
		shaderLight.setMat4f("model", glm::value_ptr(model));
		shaderLight.setMat4f("view", glm::value_ptr(view));
		shaderLight.setMat4f("projection", glm::value_ptr(projection));
		glBindVertexArray(nVaoLight);
		glDrawArrays(GL_TRIANGLES, 0, 36);

		glfwSwapBuffers(window);
		glfwPollEvents();
	}
	glDeleteBuffers(1, &nVbo);
	glDeleteVertexArrays(1, &nVao);
	glDeleteVertexArrays(1, &nVaoLight);
	glfwTerminate();

	return 0;
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
}

void keyboard_callback(GLFWwindow* window)
{
	if (GLFW_PRESS == glfwGetKey(window, GLFW_KEY_ESCAPE))
	{
		//退出
		glfwSetWindowShouldClose(window, true);
	}

	if (GLFW_PRESS == glfwGetKey(window, GLFW_KEY_W))
	{
		//向上移动
		g_camera.processKeyBoardPressed((unsigned int)enumDirect::UP, g_fDeltaTime);
	}
	if (GLFW_PRESS == glfwGetKey(window, GLFW_KEY_S))
	{
		//向下移动
		g_camera.processKeyBoardPressed((unsigned int)enumDirect::DOWN, g_fDeltaTime);
	}
	if (GLFW_PRESS == glfwGetKey(window, GLFW_KEY_A))
	{
		//向左移动
		g_camera.processKeyBoardPressed((unsigned int)enumDirect::LEFT, g_fDeltaTime);
	}
	if (GLFW_PRESS == glfwGetKey(window, GLFW_KEY_D))
	{
		//向右移动
		g_camera.processKeyBoardPressed((unsigned int)enumDirect::RIGHT, g_fDeltaTime);
	}
}

void mouse_callback(GLFWwindow* window, double xPos, double yPos)
{
	float xValue = static_cast<float>(xPos);
	float yValue = static_cast<float>(yPos);
	if (g_bFirstClick)
	{
		g_fLastX = xValue;
		g_fLastY = yValue;
		g_bFirstClick = false;
	}	

	float xOffset = g_fLastX - xValue;
	float yOffset = g_fLastY - yValue;

	g_fLastX = xValue;
	g_fLastY = yValue;

	g_camera.processMouseClicked(xOffset, yOffset);
}

void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
	g_camera.processMouseScroll(static_cast<float>(yoffset));
}
