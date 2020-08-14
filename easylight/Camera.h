#pragma once
#include<GL/glew.h>
#include<glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include<glfw3.h>
#include<iostream>


const GLfloat YAW = -90.0f;
const GLfloat PITCH = 0.0f;
const GLfloat SPEED = 3.0f;
const GLfloat SENSITIVTY = 0.25f;
const GLfloat ZOOM = 45.0f;


class Camera
{
public:
	glm::vec3 cameraPos;
	glm::vec3 cameraFront;
	glm::vec3 cameraUp;
	glm::mat4 view;
	glm::mat4 projection;

	//Eular Angles
	GLfloat Yaw;
	GLfloat Pitch;
	// Camera options
	GLfloat MovementSpeed;
	GLfloat MouseSensitivity;
	GLfloat Zoom;

public:
	Camera(glm::vec3 cameraPoss = glm::vec3(0.0f, 0.0f, 3.0f),
		glm::vec3 cameraFronts = glm::vec3(0.0f, 0.0f, -1.0f),
		glm::vec3 cameraUps = glm::vec3(0.0f, 1.0f, 0.0f)) :
		cameraPos(cameraPoss), cameraFront(cameraFronts),
		cameraUp(cameraUps), Yaw(YAW), Pitch(PITCH), MovementSpeed(SPEED),
		MouseSensitivity(SENSITIVTY), Zoom(ZOOM)
	{
		view = glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);
	}

	void changePos();
	void WPos(GLfloat cameraSpeed);
	void SPos(GLfloat cameraSpeed);
	void APos(GLfloat cameraSpeed);
	void DPos(GLfloat cameraSpeed);
	void SPACEPos(GLfloat cameraSpeed);
	 
	void ProcessMouseMovement(GLfloat xoffset, GLfloat yoffset, GLboolean constrainPitch = true);
	void changeUP() {
	}
	void ProcessMouseScroll(GLfloat yoffset);

	void Bind(GLuint Program, GLFWwindow* window);
	glm::mat4& getView();

};

