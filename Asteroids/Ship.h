#pragma once
#include "GameObject.h"
#include "Projectile.h"
#include "Particle.h"
#include "GOHittable.h"

#include <vector>
#include <memory>

class PowerUp;

class Ship : public GOHittable, public GOCollidable
{
protected:
	int score;
	int specialsLeft;
	float newDirection;
	bool extraDamage;
	bool specialAbilityActive;
	int hitTimer;
	int specialAbilityTimeCounter;
	glm::vec2 frontPosition;
	glm::vec2 rearPosition;
	float maxVelocity;
	std::vector<PowerUp*> caughtPUps;

	void shoots();
	void updateCaughtPUps();
	Particle* genParticle();
	GameObject* checkCollisions(GOHittable& goh);

	virtual void specialAbilityOn() = 0;
	virtual void specialAbilityOff() = 0;

	void updateHit();
	void incrementHitTimer() { this->hitTimer++; }
	void updateSpecialAbility();
	void move(float dt);
	void rotateLeft();
	void rotateRight();
	void accelarate(float rate);
	void slowDown(float rate);
	void updateDirection() { this->direction = this->newDirection; }

public:
	Ship(glm::vec2 pos, glm::vec2 size, std::vector<GameObject*>* pGObjects, float velocity = 0.0f, glm::ivec2 maxCoords = glm::ivec2(1920, 1080));
	Ship();
	~Ship();

	void update(float dt, std::vector<bool>& gameControls = std::vector<bool>());

	float getDirection() { return this->newDirection; }

	void setScore(int score) { if (score >= 0) this->score = score; }
	int getScore() { return this->score; }

	void incrementSpecials() { this->specialsLeft++; }
	int getSpecials() { return this->specialsLeft; }

	void setExtraDamage(bool damage) { this->extraDamage = damage; }
	bool getExtraDamage() { return this->extraDamage; }

	void setMaxVelocity(float maxVelocity) { if (maxVelocity > 0) this->maxVelocity = maxVelocity; }
	float getMaxVelocity() { return this->maxVelocity; }

	std::vector<PowerUp*>& getCaughtPUps() { return this->caughtPUps; }
};

