#include "GLVertexArray.h"
#include "GLCommondef.h"

CGLVertexArray::CGLVertexArray()
{
	glGenVertexArrays(1, &m_nRendererId);
}

CGLVertexArray::~CGLVertexArray()
{
	glDeleteVertexArrays(1, &m_nRendererId);
}

void CGLVertexArray::Bind() const
{
	GLCall(glBindVertexArray(m_nRendererId));
}

void CGLVertexArray::Unbind() const
{
	GLCall(glBindVertexArray(0));
}


void CGLVertexArray::AddBuffer(const CGLVertexBuffer& vb, const CGLVertexBufferLayout& layout)
{
	Bind();
	vb.Bind();
	std::vector<LayoutElements> elements = layout.GetElements();
	int offset = 0;
	for (size_t i = 0; i < elements.size(); ++i)
	{
		const auto& element = elements[i];
		GLCall((glEnableVertexAttribArray(i)));
		//i��Ԫ����glsl�е�λ�ã� count:���һ�����������Ԫ�ظ���
		//type:Ԫ�ص�����			normalized��������	
		//stride����ǰԪ���������еĲ��� pointer:????
		//glsl�п��԰Ѵ�������ݿ���Ϊһ����ά���飬
		//0--------
		//1--------
		//2--------
		//�ڱ����У�0�Ƕ������� 1��2

		GLCall((glVertexAttribPointer(i, element.count, element.type, element.normalized ? GL_TRUE : GL_FALSE,layout.GetStride(), (const char*)offset)));
		offset += element.count * LayoutElements::GetSizeofType(element.type);
	}
}
