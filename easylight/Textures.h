#pragma once
#include<GL/glew.h> 
#include<iostream>
#include<string>
class myTexture
{
public:
	myTexture(int i);
	myTexture();
	void Load1(const std::string str, GLuint index);
	void Load2(const std::string str, GLuint index);
	void Bind(GLuint& program);
	void Bind2(GLuint & program, int num);
	myTexture(std::string str[],int num);
	void Bind(std::string names[], int num);
	~myTexture() {
	}

private:
	GLuint* m_textures;
	int nums;
	GLuint texture1;
	GLuint texture2;
};

