#include "Framework.h"

#include <iostream>

Framework::Framework() : game(), graphics(), deltaTime(0.0f), lastFrameTime(0.0f)
{
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

	GLFWmonitor* monitor = glfwGetPrimaryMonitor();
	const GLFWvidmode* mode = glfwGetVideoMode(monitor);

	this->screenWidth = mode->width;
	this->screenHeight = mode->height;
	this->game.setWidth(this->screenWidth);
	this->game.setHeight(this->screenHeight);
	this->graphics.setWidth(this->screenWidth);
	this->graphics.setHeight(this->screenHeight);

	this->window = glfwCreateWindow(this->screenWidth, this->screenHeight, "Asteroids", monitor, nullptr);
	glfwMakeContextCurrent(this->window);

	glewExperimental = GL_TRUE;
	glewInit();
	glGetError();

	glfwSetKeyCallback(this->window, &Framework::keyCallback);

	//OGL config
	glViewport(0, 0, this->screenWidth, this->screenHeight);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	this->graphics.init();
}

Framework::~Framework() 
{
	glfwTerminate();
}

void Framework::keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GL_TRUE);

	if (key >= 0 && key < 350)
	{
		if (action == GLFW_PRESS)
			Game::setKeyValue(key, GL_TRUE);
		else if (action == GLFW_RELEASE)
			Game::setKeyValue(key, GL_FALSE);
	}
}

void Framework::gameLoop()
{
	float currentFrameTime;
	while (!glfwWindowShouldClose(this->window))
	{
		currentFrameTime = glfwGetTime();
		this->deltaTime = currentFrameTime - this->lastFrameTime;
		this->lastFrameTime = currentFrameTime;

		if (this->deltaTime < 0.016) //fps cap
			this->deltaTime = 0.016;

		glfwPollEvents(); //checking events

		if (game.getState() != GAME_ACTIVE)
			game.processInput(); //processing user input

		else
			game.update(this->deltaTime); //updating the game

		//rendering
		glClear(GL_COLOR_BUFFER_BIT); 

		this->graphics.renderGame(this->game, 1 / this->deltaTime);

		glfwSwapBuffers(this->window);
	}
}

