#include"Camera.h"

void Camera::changePos()
{
	GLfloat radius = 10.0f;
	GLfloat camX = sin(glfwGetTime()) * radius;
	GLfloat camZ = cos(glfwGetTime()) * radius;
	cameraPos = glm::vec3(camX, 0.0, camZ);
	view = glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);
}

void Camera::WPos(GLfloat cameraSpeed)
{
	cameraPos += cameraSpeed * cameraFront;
}

void Camera::SPos(GLfloat cameraSpeed)
{
	cameraPos -= cameraSpeed * cameraFront;
}

void Camera::APos(GLfloat cameraSpeed)
{
	cameraPos -= glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
}

void Camera::DPos(GLfloat cameraSpeed)
{
	cameraPos += glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
}

void Camera::SPACEPos(GLfloat cameraSpeed)
{
	cameraPos += glm::normalize(glm::vec3(0.0,1.0f,0.0f)) * cameraSpeed;
}

void Camera::CTRLPos(GLfloat cameraSpeed)
{
	cameraPos -= glm::normalize(glm::vec3(0.0, 1.0f, 0.0f)) * cameraSpeed;
}


void Camera::ProcessMouseScroll(GLfloat yoffset)
{
	if (this->Zoom >= 1.0f && this->Zoom <= 45.0f)
		this->Zoom -= yoffset;
	if (this->Zoom <= 1.0f)
		this->Zoom = 1.0f;
	if (this->Zoom >= 45.0f)
		this->Zoom = 45.0f;
}

void Camera::Bind(GLuint Program, GLFWwindow * window)
{
	GLuint transformLoc2 = glGetUniformLocation(Program, "view");
	glUniformMatrix4fv(transformLoc2, 1, GL_FALSE, glm::value_ptr(getView()));
	int width, height;
	glfwGetFramebufferSize(window, &width, &height);
	projection = glm::perspective(glm::radians(this->Zoom), float(width) / height, 0.1f, 100.0f);
	GLuint transformLoc3 = glGetUniformLocation(Program, "projection");
	glUniformMatrix4fv(transformLoc3, 1, GL_FALSE, &projection[0][0]);
}

glm::mat4 & Camera::getView()
{
	view = glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);
	return view;
}

void Camera::ProcessMouseMovement(GLfloat xoffset, GLfloat yoffset, GLboolean constrainPitch)
{
	xoffset *= this->MouseSensitivity;
	yoffset *= this->MouseSensitivity;

	this->Yaw += xoffset;
	this->Pitch += yoffset;

	// Make sure that when pitch is out of bounds, screen doesn't get flipped
	if (constrainPitch)
	{
		if (this->Pitch > 89.0f)
			this->Pitch = 89.0f;
		if (this->Pitch < -89.0f)
			this->Pitch = -89.0f;
	}

	// Update Front, Right and Up Vectors using the updated Eular angles
	glm::vec3 front;
	front.x = cos(glm::radians(Yaw)) * cos(glm::radians(Pitch));
	front.y = sin(glm::radians(Pitch));
	front.z = sin(glm::radians(Yaw)) * cos(glm::radians(Pitch));
	cameraFront = glm::normalize(front);
}