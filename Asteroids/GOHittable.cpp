#include "GOHittable.h"

GOHittable::GOHittable()
{
}

GOHittable::GOHittable(glm::vec2 pos, glm::vec2 size, float velocity, glm::ivec2 maxCoords) 
	: GameObject(pos, size, velocity, maxCoords), invincible(false), isHit(false), health(0), damage(0)
{
}

GOHittable::~GOHittable()
{
}


