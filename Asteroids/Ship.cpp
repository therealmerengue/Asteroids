#define _USE_MATH_DEFINES

#include "Ship.h"
#include "Game.h"

Ship::Ship()
{
}

Ship::~Ship()
{
}

Ship::Ship(glm::vec2 pos, glm::vec2 size, std::vector<GameObject*>* pGObjects, float velocity, glm::ivec2 maxCoords)
	: GameObject(pos, size, velocity, maxCoords), GOHittable(pos, size, velocity, maxCoords), GOCollidable(pos, size, pGObjects, velocity, maxCoords), 
	score(0), specialsLeft(2), specialAbilityTimeCounter(0), maxVelocity(velocity / 3),
	extraDamage(false), specialAbilityActive(false), hitTimer(0),
	frontPosition(glm::vec2(this->centerPosition.x, this->centerPosition.y - this->size.y / 2)),
	rearPosition(glm::vec2(this->centerPosition.x, this->centerPosition.y + this->size.y / 2))
{
	this->velocity = 0.0f;
}

void Ship::move(float dt)
{
	float velocity = this->velocity * dt;
	
	if (this->position.y >= -this->size.y && this->position.y <= this->maxCoords.y + this->size.y)
		this->position.y -= velocity * cos(this->direction);

	else
	{
		if (this->position.y < -this->size.y)
			this->position.y = this->maxCoords.y;
		else if (this->position.y > this->maxCoords.y + this->size.y)
			this->position.y = 0;
	}

	if (this->position.x >= -this->size.x && this->position.x <= this->maxCoords.x + this->size.x)
		this->position.x += velocity * sin(this->direction);

	else
	{
		if (this->position.x < -this->size.x)
			this->position.x = this->maxCoords.x;
		else if (this->position.x > this->maxCoords.x + this->size.x)
			this->position.x = 0;
	}

	this->centerPosition = glm::vec2(this->position.x + this->size.x / 2, this->position.y + this->size.y / 2);
	this->frontPosition = glm::vec2(this->centerPosition.x + this->size.x * sin(this->newDirection) / 2, this->centerPosition.y - this->size.y * cos(this->newDirection) / 2);
	this->rearPosition = glm::vec2(this->centerPosition.x - this->size.x * sin(this->newDirection) / 2, this->centerPosition.y + this->size.y * cos(this->newDirection) / 2);
	this->slowDown(1.5f);
}

void Ship::rotateLeft()
{
	this->newDirection -=  M_PI / 180;
	if (this->newDirection > 2 * M_PI)
		this->newDirection = 0;
	else if (this->newDirection < 0)
		this->newDirection = 2 * M_PI;
	
	this->frontPosition = glm::vec2(this->centerPosition.x + this->size.x * sin(this->newDirection) / 2, this->centerPosition.y - this->size.y * cos(this->newDirection) / 2);
	this->rearPosition = glm::vec2(this->centerPosition.x - this->size.x * sin(this->newDirection) / 2, this->centerPosition.y + this->size.y * cos(this->newDirection) / 2);
	this->slowDown(0.5f);
}

void Ship::rotateRight()
{
	this->newDirection +=  M_PI / 180;
	if (this->newDirection >= 2 * M_PI)
		this->newDirection = 0;
	else if (this->newDirection <= 0)
		this->newDirection = 2 * M_PI;

	this->frontPosition = glm::vec2(this->centerPosition.x + this->size.x * sin(this->newDirection) / 2, this->centerPosition.y - this->size.y * cos(this->newDirection) / 2);
	this->rearPosition = glm::vec2(this->centerPosition.x - this->size.x * sin(this->newDirection) / 2, this->centerPosition.y + this->size.y * cos(this->newDirection) / 2);
	this->slowDown(0.5f);
}

void Ship::accelarate(float rate)
{
	if (this->velocity < this->maxVelocity)
		this->velocity += rate;
}

void Ship::slowDown(float rate)
{
	if (this->velocity > 0)
		this->velocity -= rate;
}

void Ship::updateHit()
{
	if (this->getHit())
	{
		if (this->hitTimer == 20)
		{
			this->isHit = false;
			this->hitTimer = 0;
		}
		this->incrementHitTimer();
	}
}

void Ship::updateSpecialAbility()
{
	if (this->specialAbilityActive)
	{
		this->specialAbilityTimeCounter++;
		if (this->specialAbilityTimeCounter == 1000)
		{
			this->specialAbilityOff();
			this->specialAbilityTimeCounter = 0;
		}
	}
}

Particle* Ship::genParticle()
{
	return new Particle(this->rearPosition, glm::vec2(15.0f, 15.0f), -this->newDirection, this->velocity / 10, this->maxCoords);
}

GameObject* Ship::checkCollisions(GOHittable& goh)
{
	GOCollidable::checkCollisions(goh);
	if (this->collisionData.second > this->collisionData.first && !this->destroyed)
	{
		if (!this->invincible)
		{
			this->health -= goh.getDamage();
			this->isHit = true;
		}
		goh.setDestroyed(true);
	}
	return nullptr;
}

void Ship::shoots()
{
	if (this->extraDamage)
		pGObjects->push_back(new Projectile(this->frontPosition, glm::vec2(15, 15), this->pGObjects, this->newDirection, 1000.0f, 200, this->maxCoords));
	else
		pGObjects->push_back(new Projectile(this->frontPosition, glm::vec2(15, 15), this->pGObjects, this->newDirection, 1000.0f, 100, this->maxCoords));
}

void Ship::updateCaughtPUps()
{
	for (int i = 0; i < this->caughtPUps.size(); i++)
	{
		caughtPUps[i]->incrementTimer();

		if (caughtPUps[i]->getTimer() >= 400)
		{
			caughtPUps[i]->deactivatePowerUp(this);
			caughtPUps[i]->setClearable(true);
			this->caughtPUps.erase(this->caughtPUps.begin() + i);
		}
	}
}

void Ship::update(float dt, std::vector<bool>& gameControls)
{
	this->move(dt);
	(*this->pGObjects).push_back(this->genParticle());
	this->updateHit();

	if (gameControls[GLFW_KEY_UP])
	{
		this->accelarate(8.0f);
		this->updateDirection();
	}
	if (gameControls[GLFW_KEY_RIGHT])
		this->rotateRight();
	if (gameControls[GLFW_KEY_LEFT])
		this->rotateLeft();
	if (gameControls[GLFW_KEY_SPACE])
	{
		this->shoots();
		gameControls[GLFW_KEY_SPACE] = false;
	}
	if (gameControls[GLFW_KEY_LEFT_CONTROL])
	{
		this->specialAbilityOn();
		gameControls[GLFW_KEY_LEFT_CONTROL] = false;
	}

	for (int i = 0; i < (*this->pGObjects).size(); i++)
	{
		if (Asteroid* asteroid = dynamic_cast<Asteroid*>((*this->pGObjects).at(i)))
			this->checkCollisions(*asteroid); //ship vs asteroid
	}

	if (this->health <= 0)
		this->destroyed = true;

	this->updateSpecialAbility();

	this->updateCaughtPUps();
}


