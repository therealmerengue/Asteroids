#pragma once

#include <glew/glew.h>
#include <glm/glm.hpp>

#include <utility>
#include <vector>

class GameObject
{
protected:
	float velocity;
	glm::vec2 position, centerPosition, size;
	float radius;
	float direction;
	glm::ivec2 maxCoords;
	bool destroyed, clearable;
	std::string texKey;

	virtual void move(float dt) = 0;

public:
	GameObject();
	GameObject(glm::vec2 pos, glm::vec2 size, float velocity = 0.0f, glm::ivec2 maxCoords = glm::ivec2(1920, 1080));
	virtual ~GameObject();
	
	virtual void update(float dt, std::vector<bool>& gameControls = std::vector<bool>()) = 0;

	virtual float getDirection() { return this->direction; }

	void setDestroyed(bool destroyed) { this->destroyed = destroyed; }
	bool getDestroyed() { return this->destroyed; }

	void setClearable(bool clearable) { this->clearable = clearable; }
	bool getClearable() { return this->clearable; }

	float getRadius() { return this->radius; }

	float getVelocity() { return this->velocity; }

	glm::vec2 getPosition() { return this->position; }

	glm::vec2 getCenterPosition() { return this->centerPosition; }

	glm::vec2 getSize() { return this->size; }

	glm::ivec2 getMaxCoords() { return this->maxCoords; }

	std::string getTexKey() { return this->texKey; }
};

