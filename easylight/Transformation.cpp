#include"Transformation.h"

glm::mat4 Transformations::scales(glm::vec3 scale ) {
	return transform = glm::scale(transform, scale);
}
glm::mat4  Transformations::rotates(GLfloat angle, glm::vec3 rotat){
	return transform = glm::rotate(transform, glm::radians(angle), rotat);
}

glm::mat4  Transformations::translates(glm::vec3 trans ) {
	return transform = glm::translate(transform, trans);
}

glm::mat4&  Transformations::get() {
	return transform;
}

void Transformations::Bind(GLuint Program)
{
	GLuint transformLoc = glGetUniformLocation(Program, "model");
	glUniformMatrix4fv(transformLoc, 1, GL_FALSE, &transform[0][0]);

}
