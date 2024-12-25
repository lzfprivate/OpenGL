#pragma once

#include <glad.h>
#include "GLCommondef.h"
#include "GLShader.h"
#include "GLIndexBuffer.h"
#include "GLVertexArray.h"

class CGLRenderer
{
public:
	CGLRenderer();
	~CGLRenderer();

public:
	void Clear();
	void Draw(const CGLShader& shader, const CGLIndexBuffer& ib, const CGLVertexArray& va);

};


