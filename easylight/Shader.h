#pragma once
#include<GL/glew.h>
#include<glfw3.h>
#include<iostream>
#include<string>
#include<math.h>
class Shader
{
public:
	Shader(const std::string& fileName1, const std::string& fileName2);
	void setFloat(std::string str, GLfloat num);
	void Bind();
	GLuint& getProgram() { return m_program; }
	~Shader();
	GLuint m_program;
};

