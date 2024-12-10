#include "GLTexture.h"
#include "GLCommondef.h"

#include "stb_image.h"

CGLTexture::CGLTexture(const std::string& path)
	: m_nRendererID(0), m_strFilepath(path) ,m_spLocalBuffer(nullptr), 
	m_iWidth(0), m_iBitPiexl(0), m_iHeight(0)
{
	stbi_set_flip_vertically_on_load(1);
	m_spLocalBuffer = stbi_load(path.c_str(), &m_iWidth, &m_iHeight, &m_iBitPiexl, STBI_rgb_alpha);

	GLCall(glGenTextures(1, &m_nRendererID));
	GLCall(glBindTexture(GL_TEXTURE_2D, m_nRendererID));
	GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR));
	GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR));
	GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE));
	GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE));
	GLCall(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, m_iWidth, m_iHeight, 0, GL_RGBA,GL_UNSIGNED_BYTE, m_spLocalBuffer));
	GLCall(glBindTexture(GL_TEXTURE_2D, 0));

	if (m_spLocalBuffer)
		stbi_image_free(m_spLocalBuffer);



}

CGLTexture::~CGLTexture()
{
	GLCall(glDeleteTextures(1, &m_nRendererID));
}

void CGLTexture::Bind(unsigned int slots) const
{
	GLCall(glActiveTexture(GL_TEXTURE0 + slots));
	GLCall(glBindTexture(GL_TEXTURE_2D, m_nRendererID));
}

void CGLTexture::Unbind() const
{
	GLCall(glBindTexture(GL_TEXTURE_2D, 0));
}
