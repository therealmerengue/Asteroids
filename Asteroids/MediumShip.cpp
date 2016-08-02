#define _USE_MATH_DEFINES

#include "MediumShip.h"

MediumShip::MediumShip(glm::vec2 pos, glm::vec2 size, std::vector<GameObject*>* hittables, float velocity, glm::ivec2 maxCoords) :
	Ship(pos, size, hittables, velocity, maxCoords), GameObject(pos, size, velocity, maxCoords)
{
	this->health = 150;
	this->texKey = "medium";
}

MediumShip::~MediumShip()
{
}

void MediumShip::specialAbilityOn()
{
	if (!this->specialAbilityActive && this->specialsLeft >= 1)
	{
		this->damage *= 2;
		this->specialAbilityActive = true;
		this->extraDamage = true;
		this->specialsLeft--;
	}
}
void MediumShip::specialAbilityOff()
{
	if (this->specialAbilityActive)
	{
		this->damage /= 2;
		this->specialAbilityActive = false;
		this->extraDamage = false;
	}
}
