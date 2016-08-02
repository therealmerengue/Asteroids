#pragma once
#include <glew\glew.h>
#include <GLFW\glfw3.h>

#include "Game.h"
#include "Graphics.h"

class Framework 
{
private:
	int screenWidth, screenHeight;
	float deltaTime;
	float lastFrameTime;
	GLFWwindow* window;
	Game game;
	Graphics graphics;

public:	
	void gameLoop();
	static void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);

	Framework();
	~Framework();
};
