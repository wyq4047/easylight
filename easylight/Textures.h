#pragma once
#include<GL/glew.h> 
#include"stb_image.h"
#include<iostream>
#include<string>
class Texture
{
public:
	Texture(int i);
	Texture(std::string filename);
	void Bind3(GLuint & programma, std::string locname,int num);
	Texture();
	Texture(std::string filename[], int num);
	void Load1(const std::string str, GLuint index);
	void Load2(const std::string str, GLuint index);
	void Bind(GLuint& program);
	void Bind2(GLuint & program, int num);
	~Texture() {
	}

public:
	GLuint* m_textures;
	int nums;
	GLuint texture1;
	GLuint texture2;
};

