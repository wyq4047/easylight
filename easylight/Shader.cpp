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
	//glShaderSource������Ҫ�������ɫ��������Ϊ��һ��������
	//�ڶ�����ָ���˴��ݵ�Դ���ַ�������������ֻ��һ����
	//�����������Ƕ�����ɫ��������Դ�룬
	//���ĸ���������������ΪNULL��
	glCompileShader(shader);
	CheckShaderError(shader, GL_COMPILE_STATUS, false, "Error:Shader compilation failed");
	return shader;
}



Shader::Shader(const std::string& fileName1, const std::string& fileName2)
{
	 
	m_program = glCreateProgram();//����һ�����򣬲������´�����������ID����
	const std::string vertexShaderSource = LoadShader(fileName1);
	const std::string fragmentShaderSource = LoadShader(fileName2);

	//����һ����ɫ������ע�⻹����ID�����õġ��������Ǵ������������ɫ��ΪGLuint
	GLuint vertexShader;
	vertexShader = CreateShader(vertexShaderSource,GL_VERTEX_SHADER);

	//Ƭ����ɫ��
	GLuint fragmentShader;
	fragmentShader = CreateShader(fragmentShaderSource, GL_FRAGMENT_SHADER); 

	//link Program
	 
	glAttachShader(m_program, vertexShader);
	glAttachShader(m_program, fragmentShader);
	glLinkProgram(m_program);
	CheckShaderError(m_program, GL_LINK_STATUS, true, "Error:Program linking invalid");

	//�����꼴��ɾ��shader
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


//������ɫ���ļ�
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


