#pragma once

#include <glew/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "Shader.h"
#include "Texture.h"

#include <map>

class Renderer
{
protected:
	GLfloat vertices[6][4];
	Shader shader;
	GLuint VAO, VBO;

public:
	Renderer(const GLchar* vertexPath, const GLchar* fragmentPath, GLuint width = 1920, GLuint height = 1080);
	Renderer() {}
	virtual ~Renderer();
};

