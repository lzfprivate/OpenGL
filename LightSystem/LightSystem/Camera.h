#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <GLFW/glfw3.h>

enum enumDirect
{
	FRONT = 0,		//前移
	BACK,			//后移
	UP,				//上移
	DOWN,			//下移
	LEFT,			//左移
	RIGHT			//右移
};

class Camera
{
public:
	Camera(glm::vec3 pos = glm::vec3(0.0f, 0.0f, 0.0f),
		glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f),
		float yaw = 0, float pitch = 0,
		float near = -0.1f, float far = 45.0f);

	Camera(float v0, float v1, float v2,
		float v3, float v4, float v5,
		float yaw, float pitch, float near, float far);
	~Camera();



public:
	//响应键盘
	void processKeyBoardPressed(unsigned int direct, float offset);
	//响应鼠标点击
	void processMouseClicked(float xOffset, float yOffset);
	//响应鼠标滑轮
	void processMouseScroll(float offset);
	//获取lookat矩阵
	glm::mat4 getCameraMat4();

public:
	//俯仰角
	inline float yaw() const { return m_fYaw; }
	//俯仰角
	inline float pitch() const { return m_fPitch; }
	//
	inline float mouseDegree() const { return m_fMouseScrollDegree;}

private:
	void updateVector();


private:
	glm::vec3		m_vecPos;			//摄像机位置
	glm::vec3		m_vecRight;			//右向量
	glm::vec3		m_vecCameraUp;		//上向量
	glm::vec3		m_vecFront;			//前向量
	glm::vec3		m_vecWorldUp;		//世界视图上向量(0.0,1.0,0.0);



	float		m_fYaw;			//偏航角
	float		m_fPitch;		//俯仰角
	float		m_fNear;		//近平面
	float		m_fFar;			//远平面

	float		m_fKeyPressMoveSpeed;	//键盘点击速度
	float		m_fMouseScrollDegree;	//鼠标滑动角度
	float		m_fMouseMoveSensitivity;//鼠标滑动灵敏度
	

};

