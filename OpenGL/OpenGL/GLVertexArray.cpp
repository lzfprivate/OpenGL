#include "GLVertexArray.h"
#include "GLRenderer.h"

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
	for (int i = 0; i < elements.size(); ++i)
	{
		const auto& element = elements[i];
		GLCall((glEnableVertexAttribArray(i)));
		GLCall((glVertexAttribPointer(i, element.count, element.type, element.normalized ? GL_TRUE : GL_FALSE,layout.GetStride(), (const char*)offset)));
		offset += element.count * LayoutElements::GetSizeofType(element.type);
	}
  

}
