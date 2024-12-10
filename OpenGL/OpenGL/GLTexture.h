#pragma once
#include <string>

class CGLTexture
{
private:
	unsigned int m_nRendererID;
	std::string m_strFilepath;
	unsigned char* m_spLocalBuffer;
	int m_iWidth, m_iHeight,m_iBitPiexl;

public:
	CGLTexture(const std::string& path);
	~CGLTexture();

	void Bind(unsigned int slots = 0) const;
	void Unbind() const;

	inline int GetWidth() const { return m_iWidth; }
	inline int GetHeight() const { return m_iHeight; }






};

