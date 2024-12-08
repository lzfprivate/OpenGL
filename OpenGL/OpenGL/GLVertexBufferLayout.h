#pragma once
#include <vector>
#include <GL/glew.h>
#include "GLRenderer.h"

struct LayoutElements
{
	unsigned int count;			//个数
	unsigned int type;			//类型
	bool normalized;			//归一化
	LayoutElements(unsigned int type, unsigned count, bool normalized)
	{
		this->type = type;
		this->count = count;
		this->normalized = normalized;
	}
	static unsigned int GetSizeofType(unsigned type) {
		switch (type)
		{
		case GL_FLOAT:
		case GL_UNSIGNED_INT:
			return 4;
		default:
			break;
		}
		ASSERT(false);
		return 0;
	}

};
class CGLVertexBufferLayout
{
public:
	CGLVertexBufferLayout();
	~CGLVertexBufferLayout();
public:
	template <typename T>
	void Push(unsigned int count)
	{
		static_assert(false);
	}

	template<>
	void Push<float>(unsigned int count)
	{
		//count以多少个数据作为一组数据
		m_vecElements.push_back({ GL_FLOAT,count,false });
		m_nStride += sizeof(GLfloat) * count;
	}

	template<>
	void Push<unsigned int>(unsigned int count)
	{
		m_vecElements.push_back({ GL_UNSIGNED_INT,count,true });
		m_nStride += sizeof(GLuint) * count;
	}

	//TODO:添加其他类型的数据

public:
	inline unsigned int GetStride() const {
		return m_nStride;
	}
	inline std::vector<LayoutElements> GetElements() const {
		return m_vecElements;
	}

private:
	std::vector<LayoutElements>		m_vecElements;		//元素组合

	unsigned int					m_nStride;			//步进
};

