#include "LightShip.h"

LightShip::LightShip(glm::vec2 pos, glm::vec2 size, std::vector<GameObject*>* hittables, float velocity, glm::ivec2 maxCoords) :
	Ship(pos, size, hittables, velocity, maxCoords), GameObject(pos, size, velocity, maxCoords)
{
	this->health = 100;
	this->texKey = "light";
}

LightShip::~LightShip()
{
}

void LightShip::specialAbilityOn()
{
	if (!this->specialAbilityActive && this->specialsLeft >= 1)
	{
		this->velocity *= 2;
		this->specialAbilityActive = true;
		this->specialsLeft--;
	}
}

void LightShip::specialAbilityOff()
{
	if (this->specialAbilityActive)
	{
		this->velocity /= 2;
		this->specialAbilityActive = false;
	}
}
