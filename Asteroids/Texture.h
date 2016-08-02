#pragma once

#include <glew/glew.h>

class Texture
{
private:
	GLuint ID;
	GLuint width, height;
	GLuint imageFormat;
	GLuint internalFormat;
	GLuint wrapS, wrapT;
	GLuint filterMin, filterMax;

	void generateTexture(GLuint width, GLuint height, unsigned char* data);

public:
	Texture(const GLchar* texturePath, GLuint internalFormat = GL_RGBA, GLuint imageFormat = GL_RGBA, 
			GLuint wrapS = GL_REPEAT, GLuint wrapT = GL_REPEAT, GLuint filterMin = GL_LINEAR, GLuint filterMax = GL_LINEAR);
	Texture(unsigned char* textureData, GLuint textureWidth, GLuint textureHeight, GLuint internalFormat = GL_RED, GLuint imageFormat = GL_RED,
			GLuint wrapS = GL_CLAMP_TO_EDGE, GLuint wrapT = GL_CLAMP_TO_EDGE, GLuint filterMin = GL_LINEAR, GLuint filterMax = GL_LINEAR);
	Texture() {}
	~Texture();

	void bindTexture();

	GLuint getID() { return this->ID; }
};

