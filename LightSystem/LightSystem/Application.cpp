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
	Shader shaderObject("objectVertex.shader", "objectFragment.shader");
	Shader shaderLight("lightVertex.shader", "lightFragment.shader");
	unsigned int nVao, nVbo;
	
	glGenVertexArrays(1, &nVao);
	glGenBuffers(1, &nVbo);

	glBindBuffer(GL_ARRAY_BUFFER, nVbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(g_pos), g_pos, GL_STATIC_DRAW);
	
	glBindVertexArray(nVao);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 6, (void*)0);
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 6, (void*)(sizeof(float) * 3));
	glEnableVertexAttribArray(1);

	unsigned int nVaoLight;
	glGenVertexArrays(1, &nVaoLight);
	glBindVertexArray(nVaoLight);

	glBindBuffer(GL_ARRAY_BUFFER, nVbo);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 6, (void*)0);
	glEnableVertexAttribArray(0);
	
	

	while (!glfwWindowShouldClose(window))
	{
		float currentFrame = static_cast<float>(glfwGetTime());
		g_fDeltaTime = currentFrame - g_fDeltaTime;
		g_lastFrame = currentFrame;

		keyboard_callback(window);

		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		shaderObject.setVec3f("objectColor", 1.0f, 0.5f, 0.31f);
		shaderObject.setVec3f("lightColor", 1.0f, 1.0f, 1.0f);
		shaderObject.setVec3f("lightPos", 1.2f, 1.0f, 2.0f);
		shaderObject.setVec3f("material.ambient", 1.0f, 0.5f, 0.31f);
		shaderObject.setVec3f("material.diffuse", 1.0f, 0.5f, 0.31f);
		shaderObject.setVec3f("material.specular", 0.5f, 0.5f, 0.5f);	
		shaderObject.setValue1i("material.shininess", 32);

		glm::mat4 projection = glm::perspective(glm::radians(g_camera.Zoom),
			(float)(SCREEN_WIDTH / SCREEN_HEIGHT), 0.1f, 100.0f);
		glm::mat3 view = g_camera.GetViewMatrix();

		glm::mat4 model = glm::mat4(1.0);
		shaderObject.setMat4f("model", model);
		shaderObject.setMat4f("view", view);
		shaderObject.setMat4f("projection", projection);
		shaderObject.setVec3f("viewPos", g_camera.Position.x, g_camera.Position.y, g_camera.Position.z);
		shaderObject.setVec3f("light.ambient", 0.2f, 0.2f, 0.2f);
		shaderObject.setVec3f("light.diffuse", 0.5f, 0.5f, 0.5f);
		shaderObject.setVec3f("light.specular", 1.0f, 1.0f, 1.0f);
		glBindVertexArray(nVao);
		glDrawArrays(GL_TRIANGLES, 0, 36);
	
		shaderLight.setMat4f("view", view);
		shaderLight.setMat4f("projection", projection);
		model = glm::translate(model, lightPos);
		model = glm::scale(model, glm::vec3(0.2f));

		shaderLight.setMat4f("model", model);
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
		g_camera.ProcessKeyboard(Camera_Movement::FORWARD, g_fDeltaTime);
	}
	if (GLFW_PRESS == glfwGetKey(window, GLFW_KEY_S))
	{
		//向下移动
		g_camera.ProcessKeyboard(Camera_Movement::BACKWARD, g_fDeltaTime);
	}
	if (GLFW_PRESS == glfwGetKey(window, GLFW_KEY_A))
	{
		//向左移动
		g_camera.ProcessKeyboard(Camera_Movement::LEFT, g_fDeltaTime);
	}
	if (GLFW_PRESS == glfwGetKey(window, GLFW_KEY_D))
	{
		//向右移动
		g_camera.ProcessKeyboard(Camera_Movement::RIGHT, g_fDeltaTime);
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

	g_camera.ProcessMouseMovement(xOffset, yOffset);
}

void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
	g_camera.ProcessMouseScroll(static_cast<float>(yoffset));
}
