#include "SpriteRenderer.h"

SpriteRenderer::SpriteRenderer(const GLchar* vertexPath, const GLchar* fragmentPath, GLuint width, GLuint height)
	: Renderer(vertexPath, fragmentPath, width, height)
{
}

SpriteRenderer::~SpriteRenderer()
{
}

void SpriteRenderer::drawSprite(Texture &texture, glm::vec2 position, glm::vec2 size, GLfloat rotationAngle, glm::vec3 color)
{
	this->shader.useShader();
	glm::mat4 model;

	model = glm::translate(model, glm::vec3(position, 0.0f));
	model = glm::translate(model, glm::vec3(0.5f * size.x, 0.5f * size.y, 0.0f));
	model = glm::rotate(model, rotationAngle, glm::vec3(0.0f, 0.0f, 1.0f));
	model = glm::translate(model, glm::vec3(-0.5f * size.x, -0.5f * size.y, 0.0f));
	model = glm::scale(model, glm::vec3(size, 1.0f));

	this->shader.setMatrix4("model", model);
	this->shader.setVector3f("spriteColor", color);

	glActiveTexture(GL_TEXTURE0);
	texture.bindTexture();

	glBindBuffer(GL_ARRAY_BUFFER, this->VBO);
	glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(this->vertices), this->vertices);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glBindVertexArray(this->VAO);
	glDrawArrays(GL_TRIANGLES, 0, 6);
	glBindVertexArray(0);
}
