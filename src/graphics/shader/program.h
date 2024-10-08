#pragma once
#include "shader.h"

class ShaderProgram
{
private:
	GLuint _program;

public:
	ShaderProgram();
	~ShaderProgram();

	void loadShaders(string vertex_shader_filename, string fragment_shader_filename);
	void use();
};