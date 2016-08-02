#include <algorithm>

#include "GameObject.h"

GameObject::GameObject()
	: position(0, 0), size(1, 1), velocity(0.0f), direction(0.0f) {}

GameObject::GameObject(glm::vec2 pos, glm::vec2 size, float velocity, glm::ivec2 maxCoords)
	: position(pos), size(size), velocity(velocity), direction(0.0f),
	radius(0.85 * std::min(this->size.x / 2, this->size.y / 2)), maxCoords(maxCoords), destroyed(false),
	clearable(true), centerPosition(glm::vec2(this->position.x + this->size.x / 2, this->position.y + this->size.y / 2))
{ 
}

GameObject::~GameObject()
{
}

