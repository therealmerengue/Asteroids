#pragma once
#include "Renderer.h"

class TextRenderer : public Renderer
{
private:
	class Character
	{
	private:
		GLuint textureID;
		glm::ivec2 size;
		glm::ivec2 bearing;
		GLuint advance;
		friend class TextRenderer;

	public:
		TextRenderer::Character(GLuint textureID, GLuint advance, glm::ivec2 size, glm::ivec2 bearing) : 
			textureID(textureID), advance(advance), size(size), bearing(bearing) {}
		TextRenderer::Character() {}
	};

	static std::map<GLchar, TextRenderer::Character> characters;

public:
	TextRenderer(const GLchar* vertexPath, const GLchar* fragmentPath, GLuint width = 1920, GLuint height = 1080);
	~TextRenderer();

	void loadCharacters(std::string fontPath, GLuint fontSize);
	void renderText(std::string text, glm::vec2 position, GLfloat scale, glm::vec3 color = glm::vec3(1.0f));
};

