#include "GLVertexBuffer.h"
#include <glad.h>
#include "GLRenderer.h"

CGLVertexBuffer::CGLVertexBuffer(const void* data, unsigned int size) 
	: m_nRendererId(-1)
{
	glGenBuffers(1, &m_nRendererId);
	glBindBuffer(GL_ARRAY_BUFFER, m_nRendererId);
	glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
}

CGLVertexBuffer::~CGLVertexBuffer()
{
	glDeleteBuffers(1, &m_nRendererId);
}

void CGLVertexBuffer::Bind() const
{
	glBindBuffer(GL_ARRAY_BUFFER, m_nRendererId);
}

void CGLVertexBuffer::Unbind() const
{
	GLCall(glBindBuffer(GL_ARRAY_BUFFER, 0));
}
