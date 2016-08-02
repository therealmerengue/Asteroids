#include "PowerUpShield.h"

PowerUpShield::PowerUpShield()
{
}

PowerUpShield::PowerUpShield(glm::vec2 pos, glm::vec2 size, std::vector<GameObject*>* hittables, float velocity, glm::ivec2 maxCoords)
	: PowerUp(pos, size, hittables, velocity, maxCoords), GameObject(pos, size, velocity, maxCoords)
{
	this->texKey = "shield";
}

PowerUpShield::~PowerUpShield()
{
}

void PowerUpShield::activatePowerUp(Ship* ship)
{
	ship->setInvincible(true);
}

void PowerUpShield::deactivatePowerUp(Ship* ship)
{
	ship->setInvincible(false);
}
