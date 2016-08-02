#include "GOCollidable.h"

#include <memory>

GOCollidable::GOCollidable()
{
}

GOCollidable::GOCollidable(glm::vec2 pos, glm::vec2 size, std::vector<GameObject*>* pGObjects, float velocity, glm::ivec2 maxCoords)
	: GameObject(pos, size, velocity, maxCoords), pGObjects(pGObjects)
{
}

GOCollidable::~GOCollidable()
{
}

GameObject* GOCollidable::checkCollisions(GOHittable& goh)
{
	this->collisionData.first = sqrt(pow(this->centerPosition.x - goh.getCenterPosition().x, 2) + pow(this->centerPosition.y - goh.getCenterPosition().y, 2)); //distance
	this->collisionData.second = this->radius + goh.getRadius(); //radius sum
	return nullptr;
}
