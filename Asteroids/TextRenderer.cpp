#include <ft2build.h>
#include FT_FREETYPE_H

#include "TextRenderer.h"

TextRenderer::TextRenderer(const GLchar* vertexPath, const GLchar* fragmentPath, GLuint width, GLuint height) 
	: Renderer(vertexPath, fragmentPath, width, height)
{
}

TextRenderer::~TextRenderer()
{
}

void TextRenderer::loadCharacters(std::string fontPath, GLuint fontSize)
{
	this->characters.clear();

	FT_Library ft; //handle to a FreeType library instance
	if (FT_Init_FreeType(&ft)) //error if return value != 0
		std::cout << "Could not init FreeType Library" << std::endl;

	//loading a font
	FT_Face face;
	if (FT_New_Face(ft, fontPath.c_str(), 0, &face)) //calls FT_Open_Face to open a font by its pathname
		std::cout << "Failed to load font" << std::endl;

	FT_Set_Pixel_Sizes(face, 0, fontSize); //sets glyphs' sizes, width = 0 (caluculated based on height)

	glPixelStorei(GL_UNPACK_ALIGNMENT, 1); //disable byte-alignment restriction

	for (unsigned char c = 0; c < 128; c++) //pre-load/compile first 128 ASCII characters and store them
	{
		if (FT_Load_Char(face, c, FT_LOAD_RENDER)) //load character glyph 
		{
			std::cout << "Failed to load Glyph" << std::endl;
			continue;
		}

		Texture texture = Texture(face->glyph->bitmap.buffer, face->glyph->bitmap.width, face->glyph->bitmap.rows); //generating a texture for each glyph

		TextRenderer::Character character = TextRenderer::Character(texture.getID(), face->glyph->advance.x, glm::ivec2(face->glyph->bitmap.width, face->glyph->bitmap.rows), glm::ivec2(face->glyph->bitmap_left, face->glyph->bitmap_top));

		characters[c] = character;
	}
	glBindTexture(GL_TEXTURE_2D, 0);

	FT_Done_Face(face); //clearing freetype resources
	FT_Done_FreeType(ft);
}

void TextRenderer::renderText(std::string text, glm::vec2 position, GLfloat scale, glm::vec3 color)
{
	this->shader.useShader();
	this->shader.setVector3f("textColor", color);
	glActiveTexture(GL_TEXTURE0);
	glBindVertexArray(this->VAO);

	for (std::string::iterator c = text.begin(); c != text.end(); c++)
	{
		Character ch = characters[*c];

		//pushing ypos of small letters down
		float xpos = position.x + ch.bearing.x * scale;
		float ypos = position.y + (this->characters['H'].bearing.y - ch.bearing.y) * scale;

		float w = ch.size.x * scale;
		float h = ch.size.y * scale;

		// Update VBO for each character
		this->vertices[0][0] = xpos;
		this->vertices[0][1] = ypos + h;
		this->vertices[1][0] = xpos + w;
		this->vertices[1][1] = ypos;
		this->vertices[2][0] = xpos;
		this->vertices[2][1] = ypos;
		this->vertices[3][0] = xpos;
		this->vertices[3][1] = ypos + h;
		this->vertices[4][0] = xpos + w;
		this->vertices[4][1] = ypos + h;
		this->vertices[5][0] = xpos + w;
		this->vertices[5][1] = ypos;

		glBindTexture(GL_TEXTURE_2D, ch.textureID);
		glBindBuffer(GL_ARRAY_BUFFER, this->VBO); //updating VBO
		glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(this->vertices), this->vertices);
		glBindBuffer(GL_ARRAY_BUFFER, 0);

		glDrawArrays(GL_TRIANGLES, 0, 6); //rendering

		position.x += (ch.advance / 64) * scale; //move cursors for next glyph (freetype's advance value is stored in 1/64ths of a pixel)
	}
	glBindVertexArray(0);
	glBindTexture(GL_TEXTURE_2D, 0);
}

std::map<GLchar, TextRenderer::Character> TextRenderer::characters;
