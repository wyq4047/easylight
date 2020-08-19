#include <iostream> 
#include <cmath>
#include <GL/glew.h>
// GLFW
#include <glfw3.h>
#include<SOIL/SOIL.h>
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
#include"Model.h"
// Function prototypes
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
void do_movement();
extern void fillMaterials(GLuint &programma);
extern void fillLight(GLuint &programma,Camera &cm);

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
	glfwSetInputMode(display.getWindow(), GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	glewExperimental = GL_TRUE; //表明为核心模式
	if (glewInit() != GLEW_OK)
	{
		std::cout << "Failed to initialize GLEW" << std::endl;
		return -1;
	}
	// OpenGL options
	glEnable(GL_DEPTH_TEST); 
	glDepthFunc(GL_LESS);
	glEnable(GL_STENCIL_TEST);
	//stbi_set_flip_vertically_on_load(true);

	//Shader shader("./res/load_model.vs", "./res/load_model.fs");
	//char path[] = "F:/tuxinglib/backpack/backpack.obj";
	//Model mymodel(path);

	
	Shader lightingShader("./res/my_shader.vs", "./res/multilights.fs"); 
	Shader stencilShader("./res/singleColor.vs", "./res/singleColor.fs");
	Shader lampShader("./res/my_shader2.vs", "./res/my_shader2.fs");
	
	//F:\tuxinglib\backpack\backpack.ojb
	
	myVertexs vertexs;
	std::string filenames[] = {
		"./res/container2.jpg",
		"./res/container2_specular.jpg"
	};
	myTexture tx(filenames,2);
	std::string names[] = {
		"material.diffuse",
		"material.specular"
	};
	lightingShader.Bind();
	glUniform1i(glGetUniformLocation(lightingShader.m_program, "material.diffuse"), 0);
	glUniform1i(glGetUniformLocation(lightingShader.m_program, "material.specular"), 1);
	

	/*模板矩形*/
	GLfloat stencilVertices[] = {
		-0.5f, -0.5f, 0.5f, // A
		-0.5f, 0.5f, 0.5f,	// B
		-1.5f, 0.5f, 0.5f,  // C

		-1.5f, 0.5f, 0.5f,  // C
		-1.5f, -0.5f, 0.5f, // D
		-0.5f, -0.5f, 0.5f  // A
	};

	GLuint stencilVAOId, stencilVBOId;
	glGenVertexArrays(1, &stencilVAOId);
	glGenBuffers(1, &stencilVBOId);
	glBindVertexArray(stencilVAOId);
	glBindBuffer(GL_ARRAY_BUFFER, stencilVBOId);
	glBufferData(GL_ARRAY_BUFFER, sizeof(stencilVertices), stencilVertices, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GL_FLOAT), (GLvoid*)0);
	glEnableVertexAttribArray(0);
	glBindVertexArray(0);


	


	// Game loop
	while (!display.isClosed())
	{
		// Calculate deltatime of current frame
		GLfloat currentFrame = glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;
		display.Clear();//包含了glfwPollEvents
		glfwPollEvents();
		glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT| GL_STENCIL_BUFFER_BIT);
		do_movement();
		/*
		//绘制模板
		glColorMask(GL_FALSE, GL_FALSE, GL_FALSE, GL_FALSE);
		glDepthMask(GL_FALSE);
		glStencilMask(0xFF);
		glStencilFunc(GL_ALWAYS, 1, 0xFF);
		glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE);
		*/
		/*
		stencilShader.Bind();
		glm::mat4 projection = glm::perspective(camera.Zoom,
			(GLfloat)(WIDTH) / HEIGHT, 1.0f, 100.0f); // 投影矩阵
		glm::mat4 view = camera.getView(); // 视变换矩阵
		glUniformMatrix4fv(glGetUniformLocation(stencilShader.m_program, "projection"),
			1, GL_FALSE, glm::value_ptr(projection));
		glUniformMatrix4fv(glGetUniformLocation(stencilShader.m_program, "view"),
			1, GL_FALSE, glm::value_ptr(view));
		glm::mat4 model(1.0f);
		glUniformMatrix4fv(glGetUniformLocation(stencilShader.m_program, "model"),
			1, GL_FALSE, glm::value_ptr(model));
		glBindVertexArray(stencilVAOId);
		glDrawArrays(GL_TRIANGLES, 0, 6);
		
		
		// 绘制实际场景
		glColorMask(GL_TRUE, GL_TRUE, GL_TRUE, GL_TRUE);
		glDepthMask(GL_TRUE);
		glStencilMask(0x00); // 禁止写入stencil
		glStencilFunc(GL_EQUAL, 1, 0xFF);
		glStencilOp(GL_KEEP, GL_KEEP, GL_KEEP);
		*/
		/*
		shader.Bind();
		glm::mat4 projection = glm::perspective(camera.Zoom, (float)WIDTH / (float)HEIGHT, 0.1f, 100.0f);
		glm::mat4 view = camera.getView();
		glUniformMatrix4fv(glGetUniformLocation(shader.m_program, "projection"), 1, GL_FALSE, glm::value_ptr(projection));
		glUniformMatrix4fv(glGetUniformLocation(shader.m_program, "view"), 1, GL_FALSE, glm::value_ptr(view));

		glm::mat4 model(1.0f);
		model = glm::translate(model, glm::vec3(0.0f, -1.75f, 0.0f)); // Translate it down a bit so it's at the center of the scene
		model = glm::scale(model, glm::vec3(0.2f, 0.2f, 0.2f));	// It's a bit too big for our scene, so scale it down
		glUniformMatrix4fv(glGetUniformLocation(shader.m_program, "model"), 1, GL_FALSE, glm::value_ptr(model));
		mymodel.Draw(shader);
		*/

		glStencilMask(0x00);
		glStencilFunc(GL_NOTEQUAL, 1, 0xff);
		glDisable(GL_DEPTH_TEST);
		stencilShader.Bind();
		vertexs.Draw3(stencilShader.m_program);
		camera.Bind(stencilShader.m_program, display.getWindow());

		glStencilFunc(GL_ALWAYS, 1, 0xFF);
		glStencilMask(0xFF);
		glEnable(GL_DEPTH_TEST);
		lightingShader.Bind();
		vertexs.Draw1(lightingShader.m_program);
		camera.Bind(lightingShader.m_program, display.getWindow());
		GLuint viewPosLoc = glGetUniformLocation(lightingShader.m_program, "viewPos");
		glUniform3f(viewPosLoc, camera.cameraPos.x, camera.cameraPos.y, camera.cameraPos.z);
		fillMaterials(lightingShader.getProgram());
		fillLight(lightingShader.getProgram(),camera);
		tx.Bind(names, 2);

		lampShader.Bind();
		vertexs.Draw2(lampShader.getProgram());
		camera.Bind(lampShader.getProgram(), display.getWindow());
		





		glEnable(GL_DEPTH_TEST);
		glStencilMask(0xFF);  // 再次允许写入模板缓冲区 以便下次迭代时清除
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
	GLfloat cameraSpeed = 2.0f * deltaTime;

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
	if (keys[GLFW_KEY_LEFT_CONTROL]) {
		camera.CTRLPos(cameraSpeed);
	}
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