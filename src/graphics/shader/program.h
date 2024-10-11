#pragma once
#include "shader.h"
#include "glm/glm.hpp"
using namespace glm;

class ShaderProgram
{
private:
	GLuint _program;

public:
	ShaderProgram();
	~ShaderProgram();

	void setViewMatrix(mat4 view_matrix);

	void loadShaders(string vertex_shader_filename, string fragment_shader_filename);
	void use();
};