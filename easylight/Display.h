#pragma once
#define GLEW_STATIC
#include<GL/glew.h>
#include<glfw3.h>
#include<iostream>

class Display
{
public:
	Display(int w,int h , std::string title,GLFWmonitor* pt1,GLFWwindow* pt2);
	void Clear();
	void Draw();
	void setViewport();
	void setCallBack(void func(GLFWwindow* window, int key, int scancode, int action, int mode));
	bool isClosed();
	~Display();
	GLFWwindow* getWindow() { return window; }
	void destroy();

private:
	GLFWwindow* window;
};
 