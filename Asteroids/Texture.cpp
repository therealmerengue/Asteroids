#include "Texture.h"

#include <soil/SOIL.h>

Texture::Texture(const GLchar* texturePath, GLuint internalFormat, GLuint imageFormat,
				GLuint wrapS, GLuint wrapT, GLuint filterMin, GLuint filterMax) : 
				internalFormat(internalFormat), imageFormat(imageFormat), wrapS(wrapS), wrapT(wrapT), filterMin(filterMin), filterMax(filterMax)
{
	glGenTextures(1, &this->ID);

	int width, height;

	unsigned char* textureImage = SOIL_load_image(texturePath, &width, &height, 0, SOIL_LOAD_RGBA); //loading an image

	this->generateTexture(width, height, textureImage); //generating a texture

	SOIL_free_image_data(textureImage);
}

Texture::Texture(unsigned char* textureData, GLuint textureWidth, GLuint textureHeight, GLuint internalFormat, GLuint imageFormat,
				GLuint wrapS, GLuint wrapT, GLuint filterMin, GLuint filterMax) : 
				internalFormat(internalFormat), imageFormat(imageFormat), wrapS(wrapS), wrapT(wrapT), filterMin(filterMin), filterMax(filterMax)
{
	glGenTextures(1, &this->ID);
	this->generateTexture(textureWidth, textureHeight, textureData);
}

Texture::~Texture()
{
}

void Texture::generateTexture(GLuint width, GLuint height, unsigned char* data)
{
	this->width = width;
	this->height = height;

	//creating a texture
	glBindTexture(GL_TEXTURE_2D, this->ID);
	glTexImage2D(GL_TEXTURE_2D, 0, this->internalFormat, this->width, this->height, 0, this->imageFormat, GL_UNSIGNED_BYTE, data);
	
	//setting texture wrapping and filter modes
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, this->wrapS);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, this->wrapT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, this->filterMin);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, this->filterMax);

	glBindTexture(GL_TEXTURE_2D, 0);
}

void Texture::bindTexture() //to bind a texture in drawSprite in Renderer
{
	glBindTexture(GL_TEXTURE_2D, this->ID);
}