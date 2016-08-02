#pragma once
#include "Renderer.h"

class SpriteRenderer : public Renderer
{
public:
	SpriteRenderer(const GLchar* vertexPath, const GLchar* fragmentPath, GLuint width = 1920, GLuint height = 1080);
	~SpriteRenderer();

	void drawSprite(Texture &texture, glm::vec2 position, glm::vec2 size = glm::vec2(10, 10), GLfloat rotate = 0.0f, glm::vec3 color = glm::vec3(1.0f));
};

