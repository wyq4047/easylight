#include <iostream>
#include <cmath>
#include <GL/glew.h>

// GLFW
#include <glfw3.h>

// GLM Mathematics
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "Display.h"
// Other includes
#include "Shader.h"
#include "Camera.h"
#include"Vertexs.h"
#include"Textures.h"
// Function prototypes
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
void do_movement();
extern void fillMaterials(GLuint &programma);
extern void fillLight(GLuint &programma);
// Window dimensions
const GLuint WIDTH = 1920, HEIGHT = 1080;

// Camera
Camera  camera;
GLfloat lastX = WIDTH / 2.0;
GLfloat lastY = HEIGHT / 2.0;
bool    keys[1024];

// Light attributes


// Deltatime
GLfloat deltaTime = 0.0f;	// Time between current frame and last frame
GLfloat lastFrame = 0.0f;  	// Time of last frame

// The MAIN function, from here we start the application and run the game loop
int main()
{
	glfwInit();
	Display  display(WIDTH, HEIGHT, "mywindows", nullptr, nullptr);
	display.setCallBack(key_callback);
	glfwSetCursorPosCallback(display.getWindow(), mouse_callback);
	glfwSetScrollCallback(display.getWindow(), scroll_callback);

	glewExperimental = GL_TRUE; //表明为核心模式
	if (glewInit() != GLEW_OK)
	{
		std::cout << "Failed to initialize GLEW" << std::endl;
		return -1;
	}
	// OpenGL options
	glEnable(GL_DEPTH_TEST);
	// Build and compile our shader program
	Shader lightingShader("./res/my_shader.vs", "./res/my_shader.fs");
	//Shader lightingShader("./res/viewshader.vs", "./res/viewshader.fs");
	Shader lampShader("./res/my_shader2.vs", "./res/my_shader2.fs");
	myVertexs vertexs;
	std::string names[] = { 
		"./res/liuhua.jpg",
		"./res/container2_specular.jpg",
		"./res/matrix.jpg" 
	};
	Texture tx(names, 2);
	std::string strs[] = {
		"material.diffuse",
		"material.specular",
		"material.emission"
	};

	lightingShader.Bind();
	glUniform1i(glGetUniformLocation(lightingShader.m_program, "material.diffuse"), 0);
	glUniform1i(glGetUniformLocation(lightingShader.m_program, "material.specular"), 1);
	
	/*
	Texture tx("./res/container.jpg");
	std::string str1 = "material.diffuse";
	tx.Bind3(lightingShader.getProgram(), str1, 0);
	Texture tx2("./res/container2_specular.png");
	std::string str2 = "material.specular";
	tx.Bind3(lightingShader.getProgram(), str2, 1);
	Texture tx3("./res/matrix.jpg");
	std::string str3 = "material.emission";
	tx.Bind3(lightingShader.getProgram(), str3, 2);
	*/
	// Game loop
	while (!display.isClosed())
	{
		// Calculate deltatime of current frame
		GLfloat currentFrame = glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;

		display.Clear();//包含了glfwPollEvents
		do_movement();
		lightingShader.Bind();
		vertexs.Draw1(lightingShader.m_program);
		camera.Bind(lightingShader.m_program, display.getWindow());

		tx.Bind2(lightingShader.m_program, 2);
		
		
		GLuint viewPosLoc = glGetUniformLocation(lightingShader.m_program, "viewPos");
		glUniform3f(viewPosLoc, camera.cameraPos.x, camera.cameraPos.y, camera.cameraPos.z);

		fillMaterials(lightingShader.getProgram());
		fillLight(lightingShader.getProgram());


		lampShader.Bind();
		vertexs.Draw2(lampShader.getProgram());
		camera.Bind(lampShader.getProgram(), display.getWindow());
		
		glfwSwapBuffers(display.getWindow());
	}

	// Terminate GLFW, clearing any resources allocated by GLFW.
	glfwTerminate();
	return 0;
}

// Is called whenever a key is pressed/released via GLFW
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GL_TRUE);
	if (key >= 0 && key < 1024)
	{
		if (action == GLFW_PRESS)
			keys[key] = true;
		else if (action == GLFW_RELEASE)
			keys[key] = false;
	}
}

void do_movement()
{
	// Camera controls
	GLfloat cameraSpeed = 5.0f * deltaTime;

	if (keys[GLFW_KEY_W]) {
		camera.WPos(cameraSpeed);
	}
	if (keys[GLFW_KEY_S])
		camera.SPos(cameraSpeed);
	if (keys[GLFW_KEY_A])
		camera.APos(cameraSpeed);
	if (keys[GLFW_KEY_D])
		camera.DPos(cameraSpeed);
	if (keys[GLFW_KEY_SPACE])
		camera.SPACEPos(cameraSpeed);
}

bool firstMouse = true;
void mouse_callback(GLFWwindow* window,  double xpos, double ypos)
{
	 
	if (firstMouse)
	{
		lastX = xpos;
		lastY = ypos;
		firstMouse = false;
	}

	GLfloat xoffset = xpos - lastX;
	GLfloat yoffset = lastY - ypos;  // Reversed since y-coordinates go from bottom to left

	lastX = xpos;
	lastY = ypos;

	camera.ProcessMouseMovement(xoffset, yoffset);
}

void scroll_callback(GLFWwindow* window,double xoffset, double yoffset)
{
	camera.ProcessMouseScroll(yoffset);
}