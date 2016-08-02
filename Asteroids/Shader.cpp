#include "Shader.h"

#include <sstream>
#include <fstream>

Shader::Shader(const GLchar* vertexPath, const GLchar* fragmentPath)
{
	std::string vertexSource;
	std::string fragmentSource;

	std::ifstream vertexFile(vertexPath);
	std::ifstream fragmentFile(fragmentPath);
	std::stringstream vertexStream, fragmentStream;

	//reading file buffers into streams
	vertexStream << vertexFile.rdbuf();
	fragmentStream << fragmentFile.rdbuf();

	vertexFile.close();
	fragmentFile.close();

	vertexSource = vertexStream.str();
	fragmentSource = fragmentStream.str();
	
	const GLchar* cVertexSource = vertexSource.c_str();
	const GLchar* cFragmentSource = fragmentSource.c_str();

	this->compile(cVertexSource, cFragmentSource);
}

Shader::~Shader()
{
}

void Shader::compile(const GLchar* vertexSource, const GLchar* fragmentSource) //compiles shaders from their source code
{
	GLuint vertexShader, fragmentShader;

	//vertex shader compilation
	vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertexSource, NULL);
	glCompileShader(vertexShader);
	checkCompileErrors(vertexShader, VERTEX);

	//fragment shader compilation
	fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentSource, NULL);
	glCompileShader(fragmentShader);
	checkCompileErrors(fragmentShader, FRAGMENT);

	//creating a shader program
	this->ID = glCreateProgram();
	glAttachShader(this->ID, vertexShader);
	glAttachShader(this->ID, fragmentShader);
	glLinkProgram(this->ID);
	checkCompileErrors(this->ID, PROGRAM);

	//deleting shaders that are already linked to the program
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
}

void Shader::checkCompileErrors(GLuint object, ErrorType errType) //object = shader or program
{
	int success;
	char errorLog[1024];

	if (errType != PROGRAM)
	{
		glGetShaderiv(object, GL_COMPILE_STATUS, &success);
		if (!success)
		{
			glGetShaderInfoLog(object, 1024, NULL, errorLog);
			std::cout << "Shader compile-time error: Type: " << errType << "\n" << errorLog << std::endl;
		}
	}
	else
	{
		glGetProgramiv(object, GL_LINK_STATUS, &success);
		if (!success)
		{
			glGetProgramInfoLog(object, 1024, NULL, errorLog);
			std::cout << "Shader link-time error: Type: " << errType << "\n" << errorLog << std::endl;
		}
	}
}

void Shader::useShader()
{
	glUseProgram(this->ID);
}

void Shader::setInteger(const GLchar* name, GLint value)
{
	glUniform1i(glGetUniformLocation(this->ID, name), value);
}

void Shader::setVector3f(const GLchar* name, const glm::vec3& value)
{
	glUniform3f(glGetUniformLocation(this->ID, name), value.x, value.y, value.z);
}

void Shader::setMatrix4(const GLchar* name, const glm::mat4& matrix)
{
	glUniformMatrix4fv(glGetUniformLocation(this->ID, name), 1, GL_FALSE, glm::value_ptr(matrix));
}
