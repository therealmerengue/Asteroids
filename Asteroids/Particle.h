#pragma once
#include "GameObject.h"
#include "Shader.h"

class Particle : public GameObject
{
private:
	int lifeTime;

	void randomize();
	void move(float dt);

public:
	Particle(glm::vec2 pos, glm::vec2 size, float direction, float velocity, glm::ivec2 maxCoords = glm::ivec2(1920, 1080));
	~Particle();

	void update(float dt, std::vector<bool>& gameControls = std::vector<bool>());

	int getLifeTime() { return this->lifeTime; }
};

