#pragma once
#include<GL/glew.h> 
#include"stb_image.h"
#include<iostream>
#include<string>
class Texture
{
public:
	Texture(int i);
	Texture();
	void Load1(const std::string str, GLuint index);
	void Load2(const std::string str, GLuint index);
	void Bind(GLuint& program);
	void Bind2(GLuint & program, int num);
	Texture(std::string str[],int num);
	void Bind(std::string names[], int num);
	~Texture() {
	}

private:
	GLuint* m_textures;
	int nums;
	GLuint texture1;
	GLuint texture2;
};

