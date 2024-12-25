#include "GLIndexBuffer.h"
#include <glad.h>
#include "GLCommondef.h"

CGLIndexBuffer::CGLIndexBuffer(const unsigned int* data, unsigned int count) 
	: m_nRendererId(-1),m_nCount(count)
{
	//用于不同平台，所以大小可能不同
	ASSERT(sizeof(unsigned int) == sizeof(GLuint));

	glGenBuffers(1, &m_nRendererId);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_nRendererId);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(unsigned int), data, GL_STATIC_DRAW);
}

CGLIndexBuffer::~CGLIndexBuffer()
{
	glDeleteBuffers(1, &m_nRendererId);
}

void CGLIndexBuffer::Bind() const
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_nRendererId);
}

void CGLIndexBuffer::Unbind() const
{
	GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0));
}
