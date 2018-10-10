#include "gl_core_4_4.h"
#define STB_IMAGE_IMPLEMENTATION
#include <stb/stb_image.h>
#include "Texture.h"



Texture::Texture()
{
	m_filename = "None";
	m_width = 0;
	m_height = 0;
	m_glHandle = 0;
	m_format = 0;
	m_loadedPixels = nullptr;
}

Texture::Texture(const char * filename)
{
	m_filename = filename;
	m_width = 0;
	m_height = 0;
	m_glHandle = 0;
	m_format = 0;
	m_loadedPixels = nullptr;
}

Texture::Texture(unsigned int width, unsigned int height, unsigned char * pixels)
{
	m_filename = "None";
	m_width = width;
	m_height = height;
	m_glHandle = 0;
	m_loadedPixels = pixels;
}

Texture::~Texture()
{
}

bool Texture::load(const char * filename)
{
	int x = 0;
	int y = 0;
	int comp = 0;
	//This throws an error if you try to pass in m_width and m_height instead of x and y
	stbi_load(filename,&x,&y,&comp,STBI_default);
	glGenTextures(1, &m_glHandle);
	glBindTexture(GL_TEXTURE_2D, m_glHandle);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, x, y,0, GL_RGBA, GL_UNSIGNED_BYTE, m_loadedPixels);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glGenerateMipmap(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, 0);
	m_width = (unsigned int)x;
	m_height = (unsigned int)y;
	m_filename = filename;
	return true;
}

void Texture::create(unsigned int width, unsigned int height, unsigned char * pixels)
{
}

void Texture::bind(unsigned int slot) const
{
	glBindTexture(GL_TEXTURE_2D, m_glHandle);
}

