#pragma once
#include "PowerUp.h"

class PowerUpPlus : public PowerUp
{
public:
	PowerUpPlus();
	PowerUpPlus(glm::vec2 pos, glm::vec2 size, std::vector<GameObject*>* hittables, float velocity = 0.0f, glm::ivec2 maxCoords = glm::ivec2(1920, 1080));
	~PowerUpPlus();

	void activatePowerUp(Ship* ship);
};

