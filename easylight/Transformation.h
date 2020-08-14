#pragma once
#include<GL/glew.h>
#include<glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp> 
#include <glm/gtc/type_ptr.hpp>
#include<iostream>
#include<glfw3.h>
#include"Camera.h"
 

class Transformations
{
public:
	Transformations(glm::vec3 scale=glm::vec3(1.0f,1.0f,1.0f), glm::vec3 trans = glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3 rotat = glm::vec3(0.0f, 0.0f, 1.0f)) {
		this->scale = scale;
		this->trans = trans;
		this->rotat = rotat;
		this->transform = glm::mat4(1.0f);
		// 注意，我们将矩阵向我们要进行移动场景的反向移动。 
	}
	glm::mat4  scales(glm::vec3 scale = glm::vec3(1.0f, 1.0f, 1.0f));
	glm::mat4  rotates(GLfloat angle, glm::vec3 rotat = glm::vec3(1.0f, 0.0f, 1.0f));
	glm::mat4  translates(glm::vec3 trans = glm::vec3(0.0f, 0.0f, 0.0f));
	glm::mat4 & get();
	void Bind(GLuint Program);
	~Transformations() {
	}

private:
	glm::vec3 scale;
	glm::vec3 trans;
	glm::vec3 rotat;
	glm::mat4 transform; 
};

 
