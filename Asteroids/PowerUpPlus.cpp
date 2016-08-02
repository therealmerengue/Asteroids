#include "PowerUpPlus.h"

PowerUpPlus::PowerUpPlus()
{
}

PowerUpPlus::PowerUpPlus(glm::vec2 pos, glm::vec2 size, std::vector<GameObject*>* hittables, float velocity, glm::ivec2 maxCoords)
	: PowerUp(pos, size, hittables, velocity, maxCoords), GameObject(pos, size, velocity, maxCoords)
{
	this->texKey = "plus";
}

PowerUpPlus::~PowerUpPlus()
{
}

void PowerUpPlus::activatePowerUp(Ship* ship)
{
	ship->incrementSpecials();
}
