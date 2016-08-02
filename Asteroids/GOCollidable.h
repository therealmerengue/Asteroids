#pragma once
#include "GOHittable.h"

#include <memory>

class GOCollidable : public virtual GameObject
{
protected:
	std::vector<GameObject*>* pGObjects;
	std::pair<float, float> collisionData;

	virtual GameObject* checkCollisions(GOHittable& goh) = 0;

public:
	GOCollidable();
	GOCollidable(glm::vec2 pos, glm::vec2 size, std::vector<GameObject*>* pGObjects, float velocity = 0.0f, glm::ivec2 maxCoords = glm::ivec2(1920, 1080));
	~GOCollidable();

	std::pair<float, float> getCollisionData() { return this->collisionData; }
};

