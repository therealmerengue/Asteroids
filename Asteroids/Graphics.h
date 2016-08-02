#pragma once
#include <glew\glew.h>
#include <GLFW\glfw3.h>

#include "Renderer.h"
#include "SpriteRenderer.h"
#include "TextRenderer.h"
#include "Texture.h"
#include "Ship.h"
#include "Asteroid.h"
#include "PowerUp.h"
#include "GameObject.h"
#include "Game.h"

#include <map>
#include <vector>
#include <string>
#include <memory>

class Graphics
{
private:
	int width, height;
	SpriteRenderer* spriteRenderer;
	TextRenderer* textRenderer;
	static std::map<std::string, Texture> textureMap;

	void addTexture(std::string texName, Texture& texture);
	void drawObject(GameObject& object, Texture& texture, glm::vec3 color = glm::vec3(1.0f));
	void displayScreen(std::string texName);
	void drawText(std::string text, glm::vec2 position, float scale, glm::vec3 color = glm::vec3(1.0f, 1.0f, 1.0f));

public:
	Graphics();
	~Graphics();

	void init();
	void renderGame(Game& game, int FPS);

	void setWidth(int width) { this->width = width; }
	void setHeight(int height) { this->height = height; }

	static Texture& getTexture(std::string name) { return textureMap[name]; }	
};

