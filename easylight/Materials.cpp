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
glm::vec3 pointLightPositions[] = {
		glm::vec3(0.7f,  0.2f,  2.0f),
		glm::vec3(2.3f, -3.3f, -4.0f),
		glm::vec3(-4.0f,  2.0f, -12.0f),
		glm::vec3(0.0f,  0.0f, -3.0f)
};
void fillMaterials(GLuint &programma){
	//GLint matAmbientLoc = glGetUniformLocation(programma, "material.ambient");
	//GLint matDiffuseLoc = glGetUniformLocation(programma, "material.diffuse");
	//GLint matSpecularLoc = glGetUniformLocation(programma, "material.specular");
	GLint matShineLoc = glGetUniformLocation(programma, "material.shininess");

	//glUniform3f(matAmbientLoc, Ambient.x, Ambient.y, Ambient.z);
	//glUniform3f(matDiffuseLoc, Diffuse.x, Diffuse.y, Diffuse.z);
	//glUniform3f(matSpecularLoc, Specular.x, Specular.y, Specular.z);
	glUniform1f(matShineLoc, Shininess);
}

void fillLight(GLuint &programma,Camera &camera){
	//dirlight
	glUniform3f(glGetUniformLocation(programma, "dirLight.direction"), -0.2f, -1.0f, -0.3f);
	glUniform3f(glGetUniformLocation(programma, "dirLight.ambient"), 0.05f, 0.05f, 0.05f);
	glUniform3f(glGetUniformLocation(programma, "dirLight.diffuse"), 0.4f, 0.4f, 0.4f);
	glUniform3f(glGetUniformLocation(programma, "dirLight.specular"), 0.5f, 0.5f, 0.5f);

	//pointlight
	for (int i = 0; i < 4; i++) {
		glUniform3f(glGetUniformLocation(programma, ("pointLights["+std::to_string(i)+"].position").c_str()), pointLightPositions[i].x, pointLightPositions[i].y, pointLightPositions[i].z);
		glUniform3f(glGetUniformLocation(programma, ("pointLights[" + std::to_string(i) + "].ambient").c_str()), 0.05f, 0.05f, 0.05f);
		glUniform3f(glGetUniformLocation(programma, ("pointLights[" + std::to_string(i) + "].diffuse").c_str()), 0.8f, 0.8f, 0.8f);
		glUniform3f(glGetUniformLocation(programma, ("pointLights[" + std::to_string(i) + "].specular").c_str()), 1.0f, 1.0f, 1.0f);
		glUniform1f(glGetUniformLocation(programma, ("pointLights[" + std::to_string(i) + "].constant").c_str()), 1.0f);
		glUniform1f(glGetUniformLocation(programma, ("pointLights[" + std::to_string(i) + "].linear").c_str()), 0.09);
		glUniform1f(glGetUniformLocation(programma, ("pointLights[" + std::to_string(i) + "].quadratic").c_str()), 0.032);
	}

	
	glUniform3f(glGetUniformLocation(programma, "spotLight.position"), camera.cameraPos.x, camera.cameraPos.y, camera.cameraPos.z);
	glUniform3f(glGetUniformLocation(programma, "spotLight.direction"), camera.cameraFront.x, camera.cameraFront.y, camera.cameraFront.z);
	glUniform3f(glGetUniformLocation(programma, "spotLight.ambient"), 0.0f, 0.0f, 0.0f);
	glUniform3f(glGetUniformLocation(programma, "spotLight.diffuse"), 1.0f, 1.0f, 1.0f);
	glUniform3f(glGetUniformLocation(programma, "spotLight.specular"), 1.0f, 1.0f, 1.0f);
	glUniform1f(glGetUniformLocation(programma, "spotLight.constant"), 1.0f);
	glUniform1f(glGetUniformLocation(programma, "spotLight.linear"), 0.09);
	glUniform1f(glGetUniformLocation(programma, "spotLight.quadratic"), 0.032);
	glUniform1f(glGetUniformLocation(programma, "spotLight.cutOff"), glm::cos(glm::radians(12.5f)));
	glUniform1f(glGetUniformLocation(programma, "spotLight.outerCutOff"), glm::cos(glm::radians(15.0f)));


	/*
	GLint lightAmbientLoc = glGetUniformLocation(programma, "light.ambient");
	GLint lightDiffuseLoc = glGetUniformLocation(programma, "light.diffuse");
	GLint lightSpecularLoc = glGetUniformLocation(programma, "light.specular");
	GLint lightPosLoc = glGetUniformLocation(programma, "light.position");
	GLint lightSpotdirLoc = glGetUniformLocation(programma, "light.direction");
	GLuint lightSpotCutOffLoc = glGetUniformLocation(programma, "light.CutOff");
	GLuint lightSpotOutCutOffLoc = glGetUniformLocation(programma, "light.outerCutOff");
	
	glm::vec3 lightPos(1.2f, 1.0f, 2.0f);
	glUniform3f(lightPosLoc, lightPos.x, lightPos.y, lightPos.z);
	glUniform3f(lightAmbientLoc, 0.2f, 0.2f, 0.2f);
	glUniform3f(lightDiffuseLoc, 0.5f, 0.5f, 0.5f);// 让我们把这个光调暗一点，这样会看起来更自然
	glUniform3f(lightSpecularLoc, 1.0f, 1.0f, 1.0f);
	
	glUniform1f(glGetUniformLocation(programma, "light.constant"), 1.0f);
	glUniform1f(glGetUniformLocation(programma, "light.linear"), 0.022); 	
	glUniform1f(glGetUniformLocation(programma, "light.quadratic"), 0.0019);

	//glUniform3f(lightPosLoc, camera.cameraPos.x, camera.cameraPos.y, camera.cameraPos.z); 
	glUniform3f(lightSpotdirLoc, -0.2f, -1.0f, -0.3f);
	glUniform1f(lightSpotCutOffLoc, glm::cos(glm::radians(12.5f)));
	glUniform1f(lightSpotOutCutOffLoc, glm::cos(glm::radians(17.5f)));
	*/

}