#pragma once
class CGLIndexBuffer
{
private:
	unsigned int m_nRendererId;		//������ID
	unsigned int m_nCount;			//����

public:
	CGLIndexBuffer(const unsigned int* data ,unsigned int count);
	~CGLIndexBuffer();

	void Bind() const;
	void Unbind() const;

	inline unsigned int GetCount() const { return m_nCount; }

};

