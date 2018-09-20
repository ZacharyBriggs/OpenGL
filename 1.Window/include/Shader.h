#include <cstdio>
#include "gl_core_4_4.h"
#include <iostream>
#pragma once
class Shader
{
public:
	Shader();
	~Shader();
	void bind();
	void unbind();
	void load(const char* filename, unsigned int type, bool isFile = true);
	bool attach();
	void defaultLoad();

	unsigned int getUniform(const char* mvp);
	unsigned int m_vertexShader;
	unsigned int m_fragmentShader;

	const char* vsSource;
	const char* fsSource;

	unsigned int m_program;
private:
	std::string vsStr;
	std::string fsStr;
};

struct ShaderData
{
	Shader* shader;
	char* source;
	unsigned type;
	bool isFile;
};
