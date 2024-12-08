#pragma once
#include "GLVertexBuffer.h"
#include "GLVertexBufferLayout.h"


class CGLVertexArray
{
private:
	unsigned int m_nRendererId;		//������ID
	unsigned int m_nCount;			//����

public:
	CGLVertexArray();
	~CGLVertexArray();

	void Bind() const;
	void Unbind() const;

public:
	void AddBuffer(const CGLVertexBuffer& vb, const CGLVertexBufferLayout& layout);
};

