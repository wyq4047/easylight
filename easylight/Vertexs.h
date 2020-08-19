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
	void Draw3(GLuint & programma);

	~myVertexs() {
		glDeleteVertexArrays(1, &containerVAO);
		glDeleteVertexArrays(1, &lightVAO);
		glDeleteBuffers(1, &VBO);
	}
	GLuint VBO;
	GLuint containerVAO;
	GLuint lightVAO;

};





