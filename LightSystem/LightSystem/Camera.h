#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <GLFW/glfw3.h>

enum enumDirect
{
	FRONT = 0,		//ǰ��
	BACK,			//����
	UP,				//����
	DOWN,			//����
	LEFT,			//����
	RIGHT			//����
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
	//��Ӧ����
	void processKeyBoardPressed(unsigned int direct, float offset);
	//��Ӧ�����
	void processMouseClicked(float xOffset, float yOffset);
	//��Ӧ��껬��
	void processMouseScroll(float offset);
	//��ȡlookat����
	glm::mat4 getCameraMat4();

public:
	//������
	inline float yaw() const { return m_fYaw; }
	//������
	inline float pitch() const { return m_fPitch; }
	//
	inline float mouseDegree() const { return m_fMouseScrollDegree;}

private:
	void updateVector();


private:
	glm::vec3		m_vecPos;			//�����λ��
	glm::vec3		m_vecRight;			//������
	glm::vec3		m_vecCameraUp;		//������
	glm::vec3		m_vecFront;			//ǰ����
	glm::vec3		m_vecWorldUp;		//������ͼ������(0.0,1.0,0.0);



	float		m_fYaw;			//ƫ����
	float		m_fPitch;		//������
	float		m_fNear;		//��ƽ��
	float		m_fFar;			//Զƽ��

	float		m_fKeyPressMoveSpeed;	//���̵���ٶ�
	float		m_fMouseScrollDegree;	//��껬���Ƕ�
	float		m_fMouseMoveSensitivity;//��껬��������
	

};

