#include "GLRenderer.h"
#include <glad.h>
#include <GLFW/glfw3.h>
#include <iostream>




CGLRenderer::CGLRenderer()
{
}

CGLRenderer::~CGLRenderer()
{
}

void CGLRenderer::Clear()
{
    GLCall(glClear(GL_COLOR_BUFFER_BIT));
}

void CGLRenderer::Draw(const CGLShader& shader, const CGLIndexBuffer& ib, const CGLVertexArray& va)
{
    shader.Bind();
    ib.Bind();
    va.Bind();
    GLCall(glDrawElements(GL_TRIANGLES, ib.GetCount(), GL_UNSIGNED_INT, nullptr));
}
