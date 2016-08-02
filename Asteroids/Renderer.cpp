#include <glew/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <ft2build.h>
#include FT_FREETYPE_H

#include "Renderer.h"

Renderer::Renderer(const GLchar* vertexPath, const GLchar* fragmentPath, GLuint width, GLuint height) :
	vertices{ {0.0f, 1.0f, 0.0f, 1.0f},
			{1.0f, 0.0f, 1.0f, 0.0f},
			{0.0f, 0.0f, 0.0f, 0.0f},
			{0.0f, 1.0f, 0.0f, 1.0f},
			{1.0f, 1.0f, 1.0f, 1.0f},
			{1.0f, 0.0f, 1.0f, 0.0f} }
{
	this->shader = Shader(vertexPath, fragmentPath);
	this->shader.useShader();

	glm::mat4 projection = glm::ortho(0.0f, (float)width, (float)height, 0.0f, -1.0f, 1.0f);
	this->shader.setInteger("image", 0);
	this->shader.setMatrix4("projection", projection);

	glGenVertexArrays(1, &this->VAO);
	glGenBuffers(1, &this->VBO);	
	glBindBuffer(GL_ARRAY_BUFFER, this->VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * 6 * 4, NULL, GL_DYNAMIC_DRAW);
	glBindVertexArray(this->VAO);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), 0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}

Renderer::~Renderer()
{
	glDeleteBuffers(1, &this->VBO);
	glDeleteVertexArrays(1, &this->VAO);
}
