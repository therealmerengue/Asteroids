#pragma once

#include "Ship.h"

class HeavyShip : public Ship
{
private:
	void specialAbilityOn();
	void specialAbilityOff();

public:
	HeavyShip(glm::vec2 pos, glm::vec2 size, std::vector<GameObject*>* hittables, float velocity = 0.0f, glm::ivec2 maxCoords = glm::ivec2(1920, 1080));
	~HeavyShip();
};

