#include "Particle.h"

#include <chrono>
#include <random>

Particle::Particle(glm::vec2 pos, glm::vec2 size, float direction, float velocity, glm::ivec2 maxCoords) : GameObject(pos, size, velocity, maxCoords), lifeTime(15)
{
	this->position.x -= this->size.x / 2;
	this->position.y -= this->size.y / 2;

	this->randomize();
	this->texKey = "particle";
}

Particle::~Particle()
{
}

void Particle::randomize()
{
	std::default_random_engine e(std::chrono::steady_clock::now().time_since_epoch().count());
	this->position.x += (int)e() % 4;
	this->position.y += (int)e() % 4;
	this->direction = e() % 6;
}

void Particle::update(float dt, std::vector<bool>& gameControls)
{
	this->move(dt);
	this->lifeTime--;
	if (this->lifeTime <= 0)
		this->destroyed = true;
}

void Particle::move(float dt)
{
	float velocity = this->velocity * dt;

	this->position.x += velocity * sin(this->direction);
	this->position.y -= velocity * cos(this->direction);
}
