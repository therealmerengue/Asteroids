#include "Collision.h"

Collision::Collision()
{
}

Collision::Collision(glm::vec2 pos, glm::vec2 size, float velocity, glm::ivec2 maxCoords)
	: GameObject(pos, size, velocity, maxCoords)
{
}

Collision::~Collision()
{
}
