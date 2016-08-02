#pragma once
#include <glew\glew.h>
#include <GLFW\glfw3.h>
#include <irrKlang\irrKlang.h>

#include "Renderer.h"
#include "Texture.h"
#include "GameObject.h"
#include "Ship.h"
#include "Asteroid.h"
#include "PowerUp.h"

#include <map>
#include <vector>
#include <memory>

enum GameState { GAME_CONFIG, GAME_ACTIVE, GAME_OVER };

class Game 
{
private:
	GameState state;
	int width, height;
	int timeCounter;
	int finalScore;
	Ship* ship;
	static std::vector<bool> gameControls;

	std::vector<GameObject*> GObjects;

	void addAst(int numOfAsteroids);
	void eraseDestroyedObjects();

	void cleanObjects()
	{
		for (int i = 0; i < this->GObjects.size(); i++)
		{
			delete GObjects[i];
		}
		GObjects.clear();
	}

public:
	Game();
	~Game();

	void processInput();
	void update(float deltaTime);

	static bool getKeyValue(int index) { return Game::gameControls[index]; }
	static void setKeyValue(int index, bool value) { Game::gameControls[index] = value; }

	void setWidth(int width) { if (width > 0) this->width = width; }
	int getWidth() { return this->width; }
	
	void setHeight(int height) { if (height > 0) this->height = height; }
	int getHeight() { return this->height; }

	int getFinalScore() { return this->finalScore; }
	
	const std::vector<GameObject*> getObj() const { return this->GObjects; }

	Ship* getShip() { return this->ship; }

	GameState getState() { return this->state; }
};