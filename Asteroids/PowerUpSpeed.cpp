#include "PowerUpSpeed.h"

PowerUpSpeed::PowerUpSpeed()
{
}

PowerUpSpeed::PowerUpSpeed(glm::vec2 pos, glm::vec2 size, std::vector<GameObject*>* hittables, float velocity, glm::ivec2 maxCoords)
	: PowerUp(pos, size, hittables, velocity, maxCoords), GameObject(pos, size, velocity, maxCoords)
{
	this->texKey = "speed";
}

PowerUpSpeed::~PowerUpSpeed()
{
}

void PowerUpSpeed::activatePowerUp(Ship* ship)
{
	float vel = ship->getMaxVelocity();
	vel *= 1.5;
	ship->setMaxVelocity(vel);
}

void PowerUpSpeed::deactivatePowerUp(Ship* ship)
{
	float vel = ship->getMaxVelocity();
	vel /= 1.5;
	ship->setMaxVelocity(vel);
}
