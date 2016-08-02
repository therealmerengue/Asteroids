#include "PowerUp.h"

PowerUp::PowerUp()
{
}

PowerUp::~PowerUp()
{
}

PowerUp::PowerUp(glm::vec2 pos, glm::vec2 size, std::vector<GameObject*>* pGObjects, float velocity, glm::ivec2 maxCoords)
	: GOCollidable(pos, size, pGObjects, velocity, maxCoords), GameObject(pos, size, velocity, maxCoords), timer(0) 
{
}

void PowerUp::move(float dt)
{
	this->position.y += dt * this->velocity;
	this->centerPosition = glm::vec2(this->position.x + this->size.x / 2, this->position.y + this->size.y / 2);
}

GameObject* PowerUp::checkCollisions(GOHittable& goh)
{
	GOCollidable::checkCollisions(goh);
	if (this->collisionData.second > this->collisionData.first && !this->destroyed)
	{
		this->destroyed = true;
		this->clearable = false;
		dynamic_cast<Ship*>(&goh)->getCaughtPUps().push_back(this);
		this->activatePowerUp(dynamic_cast<Ship*>(&goh));
	}
	return nullptr;
}

void PowerUp::update(float dt, std::vector<bool>& gameControls)
{
	this->move(dt);
	for (int i = 0; i < (*this->pGObjects).size(); i++)
	{
		if (Ship* ship = dynamic_cast<Ship*>((*this->pGObjects).at(i)))
			this->checkCollisions(*ship);
	}
}
