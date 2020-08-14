#include"Shader.h"
#include<iostream>
#include<fstream>


static std::string LoadShader(const std::string& fileName);
static void CheckShaderError(GLuint shader, GLuint flag, bool isProgram, const std::string& errorMessage);

GLuint CreateShader(const std::string & text, GLenum shaderType)
{
	GLuint shader = glCreateShader(shaderType);
	if (shader == 0) {
		std::cerr << "Error:shader creation failure" << std::endl;
	}
	const GLchar* shaderSourceString = text.c_str();
	//GLint shaderSourceStringLength = text.length();
	glShaderSource(shader, 1, &shaderSourceString, NULL);
	//glShaderSource函数把要编译的着色器对象作为第一个参数。
	//第二参数指定了传递的源码字符串数量，这里只有一个。
	//第三个参数是顶点着色器真正的源码，
	//第四个参数我们先设置为NULL。
	glCompileShader(shader);
	CheckShaderError(shader, GL_COMPILE_STATUS, false, "Error:Shader compilation failed");
	return shader;
}



Shader::Shader(const std::string& fileName1, const std::string& fileName2)
{
	 
	m_program = glCreateProgram();//创建一个程序，并返回新创建程序对象的ID引用
	const std::string vertexShaderSource = LoadShader(fileName1);
	const std::string fragmentShaderSource = LoadShader(fileName2);

	//创建一个着色器对象，注意还是用ID来引用的。所以我们储存这个顶点着色器为GLuint
	GLuint vertexShader;
	vertexShader = CreateShader(vertexShaderSource,GL_VERTEX_SHADER);

	//片段着色器
	GLuint fragmentShader;
	fragmentShader = CreateShader(fragmentShaderSource, GL_FRAGMENT_SHADER); 

	//link Program
	 
	glAttachShader(m_program, vertexShader);
	glAttachShader(m_program, fragmentShader);
	glLinkProgram(m_program);
	CheckShaderError(m_program, GL_LINK_STATUS, true, "Error:Program linking invalid");

	//链接完即可删除shader
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);

	//glValidateProgram(m_program);
	//CheckShaderError(m_program, GL_VALIDATE_STATUS, true, "Error:Program validate invalid");

}

void Shader::setFloat(std::string str, GLfloat num) {
	GLint  Location = glGetUniformLocation(m_program, str.c_str());
	glUniform1f(Location, num);
}


void Shader::Bind()
{
	glUseProgram(m_program); 
}



Shader::~Shader()
{ 
	glDeleteProgram(m_program);
}

static void CheckShaderError(
	GLuint shader,
	GLuint flag,
	bool isProgram,
	const std::string& errorMessage
) {
	GLint success = 0;
	GLchar error[1024] = { 0 };
	if (isProgram) {
		glGetProgramiv(shader, flag, &success);
	}
	else {
		glGetShaderiv(shader, flag, &success);
	}

	if (success == GL_FALSE) {
		if (isProgram) {
			glGetProgramInfoLog(shader, sizeof(error), NULL, error);
		}
		else {
			glGetShaderInfoLog(shader, sizeof(error), NULL, error);
		}
		std::cerr << errorMessage << ":'" << error << "'" << std::endl;
	}
}


//加载着色器文件
static std::string LoadShader(const std::string& fileName)
{
	std::ifstream file;
	file.open(fileName.c_str());
	std::string output;
	std::string  line;
	if (file.is_open()) {
		while (file.good()) {
			getline(file, line);
			output.append(line + "\n");
		}
	}
	else {
		std::cerr << "Unable to load shader:" << fileName << std::endl;
	}
	return output;
}


