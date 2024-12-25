#include "Camera.h"


Camera::Camera(glm::vec3 pos, glm::vec3 up,
	float yaw, float pitch, float near, float far)
	:m_vecPos(pos),m_vecWorldUp(up),
	m_fYaw(yaw),m_fPitch(pitch),
	m_fNear(near),m_fFar(far)
{
	updateVector();
}



Camera::Camera(float v0, float v1, float v2, float v3, float v4, float v5, float yaw, float pitch, float near, float far)
	: m_vecPos(glm::vec3(v0,v1,v2)), m_vecWorldUp(glm::vec3(v3,v4,v5)),
	m_fYaw(yaw), m_fPitch(pitch), m_fNear(near), m_fFar(far)
{
	updateVector();
}


Camera::~Camera()
{
}

void Camera::processKeyBoardPressed(unsigned int direct,float offset)
{
	//修改当前位置的X轴
	switch (direct)
	{
	case enumDirect::LEFT:
	{
		m_vecPos -= m_vecRight * offset;
		break;
	}
	case enumDirect::RIGHT:
	{
		m_vecPos += m_vecRight * offset;
		break;
	}
	case enumDirect::UP:
	{
		m_vecPos += m_vecCameraUp * offset;
		break;
	}
	case enumDirect::DOWN:
	{
		m_vecPos -= m_vecCameraUp * offset;
		break;
	}
	default:
		break;
	} 
}

void Camera::processMouseClicked(float xOffset, float yOffset)
{
	//TODO:修改俯仰角和偏航角
	updateVector();
}


void Camera::processMouseScroll(float offset)
{
	//修改当前位置的Z轴
}

glm::mat4 Camera::getCameraMat4()
{
	return glm::lookAt(m_vecPos, m_vecPos + m_vecFront,m_vecCameraUp);
}

void Camera::updateVector()
{
	glm::vec3 front;
	front.x = cos(glm::radians(m_fYaw)) * cos(glm::radians(m_fPitch));
	front.y = sin(glm::radians(m_fPitch));	
	front.z = sin(glm::radians(m_fYaw)) * cos(glm::radians(m_fPitch));

	m_vecFront = glm::normalize(front);
	m_vecRight = glm::normalize(glm::cross(m_vecFront, m_vecWorldUp));
	m_vecCameraUp = glm::normalize(glm::cross(m_vecRight, m_vecFront));
}
