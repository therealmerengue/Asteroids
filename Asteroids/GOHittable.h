#pragma once
#include "GameObject.h"

class GOHittable : public virtual GameObject
{
protected:
	bool invincible;
	bool isHit;
	int health;
	int damage;

public:
	GOHittable();
	GOHittable(glm::vec2 pos, glm::vec2 size, float velocity = 0.0f, glm::ivec2 maxCoords = glm::ivec2(1920, 1080));
	~GOHittable();

	bool getInvincible() { return this->invincible; }
	void setInvincible(bool invincible) { this->invincible = invincible; }

	bool getHit() { return this->isHit; }

	int getHealth() { return this->health; }
	void setHealth(int health) { this->health = health; }

	int getDamage() { return this->damage; }
};

