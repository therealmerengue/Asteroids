#include <chrono>
#include <random>

#include "Asteroid.h"
#include "Ship.h"

Asteroid::Asteroid()
{
}

Asteroid::Asteroid(glm::vec2 pos, glm::vec2 size, std::vector<GameObject*>* pGObjects, Ship* ship, float velocity, int damage, int health, glm::ivec2 maxCoords, float direction)
	: GameObject(pos, size, velocity, maxCoords), GOHittable(pos, size, velocity, maxCoords), 
	GOCollidable(pos, size, pGObjects, velocity, maxCoords), special(false), ship(ship)
{
	this->health = health;
	this->damage = damage;
	this->direction = direction;
	this->texKey = "asteroid";
}

Asteroid::~Asteroid()
{
}

void Asteroid::randomize()
{
	std::default_random_engine e(std::chrono::steady_clock::now().time_since_epoch().count());

	float maxDirection = 6.28f;

	switch (e() % 4)
	{
	case 0:
		this->position.x = 0;
		this->position.y = ((float)e() / (float)(e.max())) * this->maxCoords.y;
		this->direction = ((float)e() / (float)(e.max())) * maxDirection / 2; //left side of the screen - direction (0, 180)
		break;
	case 1:
		this->position.x = this->maxCoords.x;
		this->position.y = ((float)e() / (float)(e.max())) * this->maxCoords.y;
		this->direction = ((float)e() / (float)(e.max())) * maxDirection / 2 + maxDirection / 2; //right side of the screen - direction (180, 360)
		break;
	case 2:
		this->position.x = ((float)e() / (float)(e.max())) * this->maxCoords.x;
		this->position.y = 0;
		this->direction = ((float)e() / (float)(e.max())) * maxDirection / 2 + maxDirection / 4; //top of the screen - direction (90, 270)
		break;
	case 3:
		this->position.x = ((float)e() / (float)(e.max())) * this->maxCoords.x;
		this->position.y = this->maxCoords.y;
		this->direction = ((float)e() / (float)(e.max())) * maxDirection / 2 - maxDirection / 4; //bottom of the screen - direction (-90, 90) 
		break;
	}

	this->centerPosition = glm::vec2(this->position.x + this->size.x / 2, this->position.y + this->size.y / 2);
}

void Asteroid::move(float dt)
{
	float velocity = this->velocity * dt;

	if (this->position.y >= -this->size.y && this->position.y <= this->maxCoords.y + this->size.y)
		this->position.y -= 0.1 * velocity * cos(this->direction);

	else
	{
		if (this->position.y < -this->size.y)
			this->position.y = this->maxCoords.y;
		else if (this->position.y > this->maxCoords.y + this->size.y)
			this->position.y = 0;
	}

	if (this->position.x >= -this->size.x && this->position.x <= this->maxCoords.x + this->size.x)
		this->position.x += 0.1 * velocity * sin(this->direction);

	else
	{
		if (this->position.x < -this->size.x)
			this->position.x = this->maxCoords.x;
		else if (this->position.x > this->maxCoords.x + this->size.x)
			this->position.x = 0;
	}

	this->centerPosition = glm::vec2(this->position.x + this->size.x / 2, this->position.y + this->size.y / 2);
}

PowerUp* Asteroid::genPowerUp(int type)
{
	switch (type)
	{
	case 0:
		return new PowerUpHealth(this->position, glm::vec2(30, 30), this->pGObjects, 150.0f, this->maxCoords);
	case 1:
		return new PowerUpSpeed(this->position, glm::vec2(30, 30), this->pGObjects, 150.0f, this->maxCoords);
	case 2:
		return new PowerUpPlus(this->position, glm::vec2(30, 30), this->pGObjects, 150.0f, this->maxCoords);
	case 3:
		return new PowerUpShield(this->position, glm::vec2(30, 30), this->pGObjects, 150.0f, this->maxCoords);
	}
}

GameObject* Asteroid::checkCollisions(GOHittable& goh)
{
	std::default_random_engine e(std::chrono::steady_clock::now().time_since_epoch().count());
	GOCollidable::checkCollisions(goh);

	if (this->collisionData.second > this->collisionData.first && !this->destroyed && !goh.getDestroyed())
	{
		this->health -= goh.getDamage();
		this->ship->setScore(this->ship->getScore() + 10);
		goh.setDestroyed(true);
		if (this->health <= 0)
			this->destroyed = true;

		if (this->destroyed && e() % 10 == 0)
			return this->genPowerUp(e() % 4);
		else if (this->destroyed && this->damage > 25)
			return new Asteroid(this->position, glm::vec2(55, 55), this->pGObjects, this->ship, this->velocity, 25, 100, this->maxCoords, this->direction);
	}

	return nullptr;
}

void Asteroid::update(float dt, std::vector<bool>& gameControls)
{
	this->move(dt);
	Projectile* projectile;
	for (unsigned int i = 0; i < (*this->pGObjects).size(); i++)
	{
		if (projectile = dynamic_cast<Projectile*>((*this->pGObjects).at(i)))
		{
			GameObject* go = this->checkCollisions(*projectile);
			if (go)
				this->pGObjects->push_back(go);
		}
	}
}