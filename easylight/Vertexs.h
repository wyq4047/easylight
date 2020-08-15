#pragma once
#include<GL/glew.h>
#include<iostream>
#include<glfw3.h>

class myVertexs
{
public:
	myVertexs();
	
	void Draw1(GLuint & programma);
	void Draw2(GLuint & programma);
	~myVertexs() {
	}
	GLuint VBO;
	GLuint containerVAO;
	GLuint lightVAO;

};





