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
		//i：元素在glsl中的位置， count:组成一组数据所需的元素个数
		//type:元素的类型			normalized：？？？	
		//stride：当前元素在数据中的步进 pointer:????
		//glsl中可以把传入的数据看成为一个二维数组，
		//0--------
		//1--------
		//2--------
		//在本例中，0是顶点坐标 1和2

		GLCall((glVertexAttribPointer(i, element.count, element.type, element.normalized ? GL_TRUE : GL_FALSE,layout.GetStride(), (const char*)offset)));
		offset += element.count * LayoutElements::GetSizeofType(element.type);
	}
}
