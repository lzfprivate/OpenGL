#pragma once

#include <GL/glew.h>


#ifndef ASSERT(x)
#define ASSERT(x) if(!(x)) __debugbreak();
#endif // !ASSERT

#ifndef GLCall(x)
#define GLCall(x) GLClearError();\
x;\
ASSERT(GLLogCall(#x,__FILE__,__LINE__))

#endif // !GLCall

//������еĴ���
void GLClearError();
//����Ƿ��д��� 
void GLCheckError();
//�����־��Ϣ
bool GLLogCall(const char* function, const char* file, int line);