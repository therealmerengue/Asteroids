#define _USE_MATH_DEFINES

#include "HeavyShip.h"

HeavyShip::HeavyShip(glm::vec2 pos, glm::vec2 size, std::vector<GameObject*>* hittables, float velocity, glm::ivec2 maxCoords) :
	Ship(pos, size, hittables, velocity, maxCoords), GameObject(pos, size, velocity, maxCoords)
{
	this->health = 200;
	this->texKey = "heavy";
}

HeavyShip::~HeavyShip()
{
}

void HeavyShip::specialAbilityOn()
{
	if (!this->specialAbilityActive && this->specialsLeft >= 1)
	{
		this->invincible = true;
		this->specialAbilityActive = true;
		this->specialsLeft--;
	}
}
void HeavyShip::specialAbilityOff()
{
	if (this->specialAbilityActive)
	{
		this->invincible = false;
		this->specialAbilityActive = false;
	}
}
