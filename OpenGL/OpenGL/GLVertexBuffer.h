#pragma once
class CGLVertexBuffer
{
private:
	unsigned int m_nRendererId;		//������ID

public:
	CGLVertexBuffer(const void* data ,unsigned int size);
	~CGLVertexBuffer();

	void Bind() const;
	void Unbind() const;

};

