#pragma once
#include "GameObject.h"
#include "GOHittable.h"
#include "GOCollidable.h"

class Projectile : public GOHittable
{
private:
	void move(float dt);

public:
	Projectile();
	Projectile(glm::vec2 pos, glm::vec2 size, std::vector<GameObject*>* pGObjects, float direction, float velocity = 0.0f, int damage = 100, glm::ivec2 maxCoords = glm::ivec2(1920, 1080));
	~Projectile();

	void update(float dt, std::vector<bool>& gameControls = std::vector<bool>());
};

