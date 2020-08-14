#include"Display.h"


Display::Display(int w, int h, std::string title, GLFWmonitor* pt1, GLFWwindow* pt2)
{
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);//���汾��:3
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);//���汾��:3
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);//OPENGLģʽ:����ģʽ
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);//�Ƿ������С�ı�
	this->window = glfwCreateWindow(w, h, title.c_str(), pt1, pt2);
	if (window == nullptr)
	{
		std::cerr << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return;
	}
	std::cerr << "this........" << std::endl;
	glfwMakeContextCurrent(window);//�ô���Ƕ�뵱ǰ�߳���
	this->setViewport();
}


void Display::Clear() {
	glfwPollEvents();
	glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}
void Display::Draw() {
	
	
	glfwSwapBuffers(this->window);
}

void Display::setViewport()
{
	int width, height;
	glfwGetFramebufferSize(window, &width, &height);
	glViewport(0, 0, width, height);//�����ӿ�
}

void Display::setCallBack(void func(GLFWwindow* window, int key, int scancode, int action, int mode))
{
	glfwSetKeyCallback(window, func);
}

bool Display::isClosed()
{
	return glfwWindowShouldClose(window);
}

Display::~Display()
{
	glfwTerminate();
}
void Display::destroy() {
	glfwTerminate();
}


