#include "GLCommondef.h"

void GLClearError()
{
	while (glGetError() != GL_NO_ERROR);
}

void GLCheckError()
{
	while (GLenum num = glGetError())
		std::cout << "OPENGL ERROR : " << num << std::endl;
}

bool GLLogCall(const char* function, const char* file, int line)
{
    while (GLenum error = glGetError())
    {
        std::cout << "OPENGL ERROR : " << error <<
            "function" << function <<
            " line" << line <<
            " file" << file << std::endl;
        return false;
    }
    return true;
}