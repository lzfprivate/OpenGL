#pragma once
#include "GLVertexBuffer.h"
#include "GLVertexBufferLayout.h"


class CGLVertexArray
{
private:
	unsigned int m_nRendererId;		//»º³åÇøID
	unsigned int m_nCount;			//¸öÊý

public:
	CGLVertexArray();
	~CGLVertexArray();

	void Bind() const;
	void Unbind() const;

public:
	void AddBuffer(const CGLVertexBuffer& vb, const CGLVertexBufferLayout& layout);
};

