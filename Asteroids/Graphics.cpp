
#include <glew/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "Graphics.h"
#include "Shader.h"
#include "Game.h"

#include <string>

Graphics::Graphics()
{
}

Graphics::~Graphics()
{
	delete this->spriteRenderer;
	delete this->textRenderer;
}

void Graphics::init()
{
	this->spriteRenderer = new SpriteRenderer("shaders/vertex.vs", "shaders/fragment.frag", this->width, this->height);
	this->textRenderer = new TextRenderer("shaders/text.vs", "shaders/text.frag", this->width, this->height);

	this->textRenderer->loadCharacters("fonts/UVF BankGothic Md BT.ttf", 50);

	this->addTexture("background", Texture("textures/background.png"));
	this->addTexture("configscreen", Texture("textures/loadingscreen.png"));
	this->addTexture("gameoverscreen", Texture("textures/gameoverscreen.png"));
	this->addTexture("light", Texture("textures/lightship.png"));
	this->addTexture("medium", Texture("textures/mediumship.png"));
	this->addTexture("heavy", Texture("textures/heavyship.png"));
	this->addTexture("asteroid", Texture("textures/bigasteroid.png"));
	this->addTexture("particle", Texture("textures/particle.png"));
	this->addTexture("plus", Texture("textures/powerupplus.png"));
	this->addTexture("health", Texture("textures/poweruphealth.png"));
	this->addTexture("speed", Texture("textures/powerupspeed.png"));
	this->addTexture("shield", Texture("textures/powerupshield.png"));
	this->addTexture("projectile", Texture("textures/projectile.png"));
	this->addTexture("particle", Texture("textures/particle.png"));
}

void Graphics::renderGame(Game& game, int FPS)
{
	if (game.getState() == GAME_ACTIVE)
	{
		this->displayScreen("background");

		Ship* ship = game.getShip();
		if (ship->getInvincible())
			this->drawObject(*ship, getTexture(ship->getTexKey()), glm::vec3(0.0f, 1.0f, 0.0f));
		else if (ship->getHit())
			this->drawObject(*ship, getTexture(ship->getTexKey()), glm::vec3(1.0f, 0.0f, 0.0f));
		else
			this->drawObject(*ship, getTexture(ship->getTexKey()));

		for (int i = 1; i < game.getObj().size(); i++)
		{
			if (!game.getObj()[i]->getDestroyed())
				this->drawObject(*game.getObj()[i], getTexture(game.getObj()[i]->getTexKey()));
		}

		this->drawText("Health: " + std::to_string(game.getShip()->getHealth()), glm::vec2(this->width - 410.0f, 15.0f), 1.0f, glm::vec3(0.496f, 0.496f, 0.613f));

		this->drawText("Score: " + std::to_string(game.getShip()->getScore()), glm::vec2(15.0f, 15.0f), 1.0f, glm::vec3(0.496f, 0.496f, 0.613f));

		this->drawText("Special abilities left: " + std::to_string(game.getShip()->getSpecials()), glm::vec2(this->width / 2 - 270.0f, 15.0f), 1.0f, glm::vec3(0.496f, 0.496f, 0.613f));

		this->drawText("FPS: " + std::to_string(FPS), glm::vec2(0.0f, 100.0f), 1.0f, glm::vec3(0.496f, 0.496f, 0.613f));
	}
	else if (game.getState() == GAME_CONFIG)
		this->displayScreen("configscreen");
	else
	{
		this->displayScreen("gameoverscreen");
		this->drawText(std::to_string(game.getFinalScore()), glm::vec2(this->width / 2, this->height / 2), 1.5f, glm::vec3(0.496f, 0.496f, 0.613f));
	}
}

void Graphics::drawObject(GameObject& object, Texture& texture, glm::vec3 color)
{
	this->spriteRenderer->drawSprite(texture, object.getPosition(), object.getSize(), object.getDirection(), color);
}

void Graphics::drawText(std::string text, glm::vec2 position, float scale, glm::vec3 color)
{
	this->textRenderer->renderText(text, position, scale, color);
}

void Graphics::displayScreen(std::string texName)
{
	this->spriteRenderer->drawSprite(Graphics::textureMap[texName], glm::vec2(0, 0), glm::vec2(this->width, this->height));
}

void Graphics::addTexture(std::string texName, Texture& texture)
{
	Graphics::textureMap[texName] = texture;
}

std::map<std::string, Texture> Graphics::textureMap;