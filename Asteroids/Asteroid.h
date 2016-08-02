#pragma once
#include "GameObject.h"
#include "GOHittable.h"
#include "Ship.h"
#include "PowerUp.h"
#include "PowerUpSpeed.h"
#include "PowerUpHealth.h"
#include "PowerUpShield.h"
#include "PowerUpPlus.h"
#include "Projectile.h"

class Asteroid : public GOHittable, public GOCollidable
{
private:
	bool special;
	Ship* ship;

	void move(float dt);
	GameObject* checkCollisions(GOHittable& goh);
	PowerUp* genPowerUp(int type);

public:
	Asteroid();
	Asteroid(glm::vec2 pos, glm::vec2 size, std::vector<GameObject*>* pGObjects, Ship* ship, float velocity = 0.0f, int damage = 25, int health = 100, glm::ivec2 maxCoords = glm::ivec2(1920, 1080), float direction = 0.0f);
	~Asteroid();

	void randomize();

	void update(float dt, std::vector<bool>& gameControls = std::vector<bool>());

	bool getSpecial() { return this->special; }
};

