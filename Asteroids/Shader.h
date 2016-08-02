#pragma once

#include <glew\glew.h>
#include <GLFW\glfw3.h>
#include <glew/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <iostream>

class Shader
{
private:
	GLuint ID;
	enum ErrorType { VERTEX, FRAGMENT, PROGRAM } errType;

	void compile(const GLchar* vertexSource, const GLchar* fragmentSource);
	void checkCompileErrors(GLuint object, ErrorType errType);

public:
	void useShader();

	void setInteger(const GLchar* name, GLint value);
	void setVector3f(const GLchar* name, const glm::vec3& value);
	void setMatrix4(const GLchar* name, const glm::mat4& matrix);

	Shader(const GLchar* vertexPath, const GLchar* fragmentPath);
	Shader() {}
	~Shader();
};

