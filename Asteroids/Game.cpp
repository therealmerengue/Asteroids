
#include <glew/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <cmath>
#include <cstdio>
#include <iostream>
#include <cstdlib>
#include <string>
#include <random>
#include <chrono>

#include "Game.h"
#include "Shader.h"
#include "LightShip.h"
#include "MediumShip.h"
#include "HeavyShip.h"
#include "Graphics.h"
#include "PowerUpPlus.h"
#include "PowerUpShield.h"

Game::Game() : state(GAME_CONFIG), timeCounter(0), GObjects(std::vector<GameObject*>()), finalScore(0)
{	
}

Game::~Game()
{
	this->cleanObjects();
}

void Game::processInput()
{
	if (this->state == GAME_CONFIG) //choosing a ship
	{
		if (gameControls[GLFW_KEY_1] || gameControls[GLFW_KEY_KP_1])
		{
			this->ship = new LightShip(glm::vec2(this->width / 2, this->height / 2), glm::vec2(85, 85), &this->GObjects, 450.0f, glm::ivec2(this->width, this->height));
			this->GObjects.push_back(this->ship);
			this->state = GAME_ACTIVE;
			this->addAst(10);
			this->timeCounter = 0;
		}
		if (gameControls[GLFW_KEY_2] || gameControls[GLFW_KEY_KP_2])
		{
			this->ship = new MediumShip(glm::vec2(this->width / 2, this->height / 2), glm::vec2(95, 95), &this->GObjects, 375.0f, glm::ivec2(this->width, this->height));
			this->GObjects.push_back(this->ship);
			this->state = GAME_ACTIVE;
			this->addAst(10);
			this->timeCounter = 0;
		}
		if (gameControls[GLFW_KEY_3] || gameControls[GLFW_KEY_KP_3])
		{
			this->ship = new HeavyShip(glm::vec2(this->width / 2, this->height / 2), glm::vec2(105, 105), &this->GObjects, 300.0f, glm::ivec2(this->width, this->height));
			this->GObjects.push_back(this->ship);
			this->state = GAME_ACTIVE;
			this->addAst(10);
			this->timeCounter = 0;
		}
	}
	else if (this->state == GAME_OVER)
	{
		if (gameControls[GLFW_KEY_ENTER])
		{
			this->cleanObjects();
			this->state = GAME_CONFIG;
		}
	}
}

void Game::update(float deltaTime)
{
	std::default_random_engine e(std::chrono::steady_clock::now().time_since_epoch().count());

	for (int i = 0; i < this->GObjects.size(); i++)
		GObjects[i]->update(deltaTime, gameControls);

	if (this->ship->getDestroyed())
	{
		this->state = GAME_OVER;
		this->finalScore = this->ship->getScore();
	}

	if (this->timeCounter % 200 == 0)
	{
		double time = glfwGetTime() / 60;
		int numOfAsteroids = e() % ((int)time + 2) + 1;
		this->addAst(numOfAsteroids);
		this->timeCounter = 0;
	}

	this->eraseDestroyedObjects();

	this->timeCounter++;
}

void Game::addAst(int numOfAsteroids)
{
	std::default_random_engine e(std::chrono::steady_clock::now().time_since_epoch().count());
	Asteroid* ast = nullptr;
	
	for (int i = 0; i < numOfAsteroids; i++)
	{
		switch (e() % 2)
		{
		case 0:
			ast = new Asteroid(glm::vec2(0, 0), glm::vec2(55, 55), &this->GObjects, this->ship, 1400.0f, 25, 100, glm::ivec2(this->width, this->height));
			ast->randomize();
			break;
		case 1:
			ast = new Asteroid(glm::vec2(0, 0), glm::vec2(110, 110), &this->GObjects, this->ship, 1000.0f, 50, 200, glm::ivec2(this->width, this->height));
			ast->randomize();
			break;
		default:
			ast = new Asteroid(glm::vec2(0, 0), glm::vec2(55, 55), &this->GObjects, this->ship, 1400.0f, 25, 100, glm::ivec2(this->width, this->height));
			ast->randomize();
			break;
		}

		this->GObjects.push_back(ast);
	}
}

void Game::eraseDestroyedObjects()
{
	for (int i = 0; i < this->GObjects.size(); i++)
	{
		if (this->GObjects[i]->getDestroyed() && this->GObjects[i]->getClearable())
		{
			delete this->GObjects[i];
			this->GObjects.erase(this->GObjects.begin() + i);
		}
	}
}

std::vector<bool> Game::gameControls = std::vector<bool>(350);