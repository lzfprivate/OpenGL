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

//清除所有的错误
void GLClearError();
//检查是否有错误 
void GLCheckError();
//输出日志信息
bool GLLogCall(const char* function, const char* file, int line);