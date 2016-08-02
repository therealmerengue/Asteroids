#pragma once

#include "PowerUp.h"

class PowerUpSpeed : public PowerUp
{
public:
	PowerUpSpeed();
	PowerUpSpeed(glm::vec2 pos, glm::vec2 size, std::vector<GameObject*>* hittables, float velocity = 0.0f, glm::ivec2 maxCoords = glm::ivec2(1920, 1080));
	~PowerUpSpeed();

	void activatePowerUp(Ship* ship);
	void deactivatePowerUp(Ship* ship);
};

