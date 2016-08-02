#include "Projectile.h"
#include "PowerUp.h"

#include <chrono>
#include <random>

Projectile::Projectile()
{
}

Projectile::~Projectile()
{
}

Projectile::Projectile(glm::vec2 pos, glm::vec2 size, std::vector<GameObject*>* pGObjects, float direction, float velocity, int damage, glm::ivec2 maxCoords)
	: GameObject(pos, size, velocity, maxCoords), GOHittable(pos, size, velocity, maxCoords)
{
	this->position.x -= this->size.x / 2;
	this->direction = direction;
	this->damage = damage;
	this->texKey = "projectile";
}

void Projectile::move(float dt)
{
	float velocity = this->velocity * dt;

	this->position.x += velocity * sin(this->direction);
	this->position.y -= velocity * cos(this->direction);

	this->centerPosition = glm::vec2(this->position.x + this->size.x / 2, this->position.y + this->size.y / 2);
}

void Projectile::update(float dt, std::vector<bool>& gameControls)
{
	this->move(dt);
	if (this->getPosition().x > this->getMaxCoords().x || this->getPosition().x < 0 || this->getPosition().y > this->getMaxCoords().y || this->getPosition().y < 0)
		this->destroyed = true;
}
