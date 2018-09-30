#define GLM_FORCE_SWIZZLE
#include "Shader.h"
#include <cstdio>
#include "gl_core_4_4.h"
#include <iostream>



Shader::Shader()
{
	m_program = glCreateProgram();
}

Shader::~Shader()
{
}

void Shader::bind()
{
	glUseProgram(m_program);
}

void Shader::unbind()
{
	glUseProgram(0);
}

//8. Ability to load shaders from file using a Shader class object.
//Takes in the name of the file and the type of the file.
//0 is a vertex shader. 1 is a fragment shader.
void Shader::load(const char * filename, unsigned int type)
{
	//Error code incase something goes wrong.
	errno_t err;
	//Make a file variable so we can find and open the file.
	FILE *fp;
	//Look for the file and open it for reading
	err = fopen_s(&fp, filename, "r");
	//We make a buffer of sufficent size to store all the data.
	char buf[500];
	//A string to appened the buffered data to.
	std::string str;
	//Open the file and loop through while there is data in the file that hasn't been buffered.
	while (std::fgets(buf, sizeof buf, fp))
	{
		//Depending on the type we append the buffered data to a vertex or fragment string
		if (type == 0)
			vsStr.append(buf);
		if (type == 1)
			fsStr.append(buf);
	}
	//We assign the data to one of the member variables depending on the type.
	if (type == 0)
		vsSource = vsStr.c_str();
	if (type == 1)
		fsSource = fsStr.c_str();
}

bool Shader::attach()
{
	m_vertexShader = glCreateShader(GL_VERTEX_SHADER);
	m_fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(m_vertexShader, 1, (const char**)&vsSource, 0);
	glCompileShader(m_vertexShader);
	glShaderSource(m_fragmentShader, 1, (const char**)&fsSource, 0);
	glCompileShader(m_fragmentShader);
	glAttachShader(m_program, m_vertexShader);
	glAttachShader(m_program, m_fragmentShader);
	glLinkProgram(m_program);

	int success = GL_FALSE;
	// check that it compiled and linked correctly
	glGetProgramiv(m_program, GL_LINK_STATUS, &success);
	if (success == GL_FALSE) {
		int infoLogLength = 0;
		glGetProgramiv(m_program, GL_INFO_LOG_LENGTH, &infoLogLength);
		char* infoLog = new char[infoLogLength + 1];
		glGetProgramInfoLog(m_program, infoLogLength, 0, infoLog);
		printf("Error: Failed to link shader program!\n");
		printf("%s\n", infoLog);
		delete[] infoLog;
	}
	return true;
}

void Shader::defaultLoad()
{
	vsSource = "#version 410\n \
                layout(location = 0) in vec4 Position; \
                layout(location = 1) in vec4 Color; \
                out vec4 vColor; \
                uniform mat4 ProjectionViewWorld; \
                void main() { vColor = Color; \
                gl_Position = ProjectionViewWorld * Position; }";

	fsSource = "#version 410\n \
                in vec4 vColor; \
                out vec4 FragColor; \
                void main() { FragColor = vColor; }";
}

unsigned int Shader::getUniform(const char *mvp)
{
	return glGetUniformLocation(m_program, mvp);;
}
