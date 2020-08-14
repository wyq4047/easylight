#include"Camera.h"
#include"Shader.h"
#include<iostream>
#include<string>
#include<vector>
#include<sstream>

glm::vec3 fun(std::string sentence="0	0	0") {  
	std::vector<std::string> v;
	std::istringstream iss(sentence);
	std::string item;
	glm::vec3 rs(1.0f);
	while (std::getline(iss, item, '\t')) {
		v.push_back(item);
	}
	for (int i = 0; i < v.size(); i++) {
		std::stringstream ss;
		ss << v[i];
		ss >> rs[i]; 
	}
	return rs;
}



glm::vec3 Ambient = fun("0.1745	0.01175	0.01175");
glm::vec3 Diffuse = glm::vec3(0.61424,0.04136,0.04136);
glm::vec3 Specular = glm::vec3(0.727811, 0.626959, 0.626959);
GLfloat Shininess = 32;
void fillMaterials(GLuint &programma){
	GLint matAmbientLoc = glGetUniformLocation(programma, "material.ambient");
	GLint matDiffuseLoc = glGetUniformLocation(programma, "material.diffuse");
	GLint matSpecularLoc = glGetUniformLocation(programma, "material.specular");
	GLint matShineLoc = glGetUniformLocation(programma, "material.shininess");

	glUniform3f(matAmbientLoc, Ambient.x, Ambient.y, Ambient.z);
	glUniform3f(matDiffuseLoc, Diffuse.x, Diffuse.y, Diffuse.z);
	glUniform3f(matSpecularLoc, Specular.x, Specular.y, Specular.z);
	glUniform1f(matShineLoc, Shininess);
}

void fillLight(GLuint &programma){

	GLint lightAmbientLoc = glGetUniformLocation(programma, "light.ambient");
	GLint lightDiffuseLoc = glGetUniformLocation(programma, "light.diffuse");
	GLint lightSpecularLoc = glGetUniformLocation(programma, "light.specular");
	GLint lightPosLoc = glGetUniformLocation(programma, "light.position");
	
	glm::vec3 lightPos(1.2f, 1.0f, 2.0f);
	glUniform3f(lightPosLoc, lightPos.x, lightPos.y, lightPos.z);
	glUniform3f(lightAmbientLoc, 0.2f, 0.2f, 0.2f);
	glUniform3f(lightDiffuseLoc, 0.5f, 0.5f, 0.5f);// 让我们把这个光调暗一点，这样会看起来更自然
	glUniform3f(lightSpecularLoc, 1.0f, 1.0f, 1.0f);

}