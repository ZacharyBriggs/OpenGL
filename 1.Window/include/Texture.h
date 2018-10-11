#pragma once
#include <string>
class Texture
{
public:
	Texture();
	~Texture();
	Texture(const char* filename);
	Texture(unsigned int width, unsigned int height, unsigned char* pixels = nullptr);

	// load a jpg, bmp, png or tga
	bool load(const char* filename);

	// creates a texture that can be filled in with pixels
	void create(unsigned int width, unsigned int height, unsigned char* pixels = nullptr);

	// returns the filename or "none" if not loaded from a file
	const std::string& getFilename() const { return m_filename; }

	// binds the texture to the specified slot
	void bind(unsigned int slot) const;
	void unbind(unsigned int slot) const;

	// returns the opengl texture handle
	unsigned int getHandle() const { return m_glHandle; }

	unsigned int getWidth() const { return m_width; }
	unsigned int getHeight() const { return m_height; }
	const unsigned char* getPixels() const { return m_loadedPixels; }

protected:

	std::string		m_filename;
	unsigned int	m_width;
	unsigned int	m_height;
	unsigned int	m_glHandle;
	unsigned char*	m_loadedPixels;
};

