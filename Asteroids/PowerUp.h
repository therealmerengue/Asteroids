#pragma once
#include "GameObject.h"
#include "Ship.h"
#include "GOCollidable.h"
#include "GOHittable.h"

class PowerUp : public GOCollidable
{
protected:
	int timer;

	void move(float dt);
	GameObject* checkCollisions(GOHittable& goh);

	virtual void activatePowerUp(Ship* ship) = 0;
	

public:
	PowerUp();
	PowerUp(glm::vec2 pos, glm::vec2 size, std::vector<GameObject*>* pGObjects, float velocity = 0.0f, glm::ivec2 maxCoords = glm::ivec2(1920, 1080));
	~PowerUp();

	void update(float dt, std::vector<bool>& gameControls = std::vector<bool>());

	virtual void deactivatePowerUp(Ship* ship) {}

	void incrementTimer() { this->timer++; }
	int getTimer() { return this->timer; }
};

