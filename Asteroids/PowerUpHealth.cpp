#include "PowerUpHealth.h"

PowerUpHealth::PowerUpHealth()
{
}

PowerUpHealth::PowerUpHealth(glm::vec2 pos, glm::vec2 size, std::vector<GameObject*>* hittables, float velocity, glm::ivec2 maxCoords)
	: PowerUp(pos, size, hittables, velocity, maxCoords), GameObject(pos, size, velocity, maxCoords)
{
	this->texKey = "health";
}

PowerUpHealth::~PowerUpHealth()
{
}

void PowerUpHealth::activatePowerUp(Ship* ship)
{
	ship->setHealth(ship->getHealth() + 50);
	//std::cout << "health\n";
}

void PowerUpHealth::deactivatePowerUp(Ship* ship)
{
}
