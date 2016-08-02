#pragma once
#include "PowerUp.h"

class PowerUpShield : public PowerUp
{
public:
	PowerUpShield();
	PowerUpShield(glm::vec2 pos, glm::vec2 size, std::vector<GameObject*>* hittables, float velocity, glm::ivec2 maxCoords = glm::ivec2(1920, 1080));
	~PowerUpShield();

	void activatePowerUp(Ship* ship);
	void deactivatePowerUp(Ship* ship);
};

