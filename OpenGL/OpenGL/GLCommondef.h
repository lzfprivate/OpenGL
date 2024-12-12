#pragma once


#include <GL/glew.h>
#include <iostream>


#ifndef ASSERT(x) 
#define ASSERT(x) if(!(x)) __debugbreak();
#endif // !ASSERT

#ifndef GLCall(x)
#define GLCall(x) GLClearError();\
x;\
ASSERT(GLLogCall(#x,__FILE__,__LINE__))

#endif // !GLCall


void GLClearError();


void GLCheckError();


bool GLLogCall(const char* function, const char* file, int line);

