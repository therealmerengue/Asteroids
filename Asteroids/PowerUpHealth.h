#pragma once
#include "PowerUp.h"

class PowerUpHealth : public PowerUp
{
public:
	PowerUpHealth();
	PowerUpHealth(glm::vec2 pos, glm::vec2 size, std::vector<GameObject*>* hittables, float velocity = 0.0f, glm::ivec2 maxCoords = glm::ivec2(1920, 1080));
	~PowerUpHealth();

	void activatePowerUp(Ship* ship);
	void deactivatePowerUp(Ship* ship);
};

