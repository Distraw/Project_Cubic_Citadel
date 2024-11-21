#pragma once
#include "shader.h"
#include "glm/glm.hpp"
using namespace glm;

class ShaderProgram
{
private:
	GLuint _program;

	GLint _model_location;
	GLint _view_location;
	GLint _projection_location;
	GLint _texture_location;
public:
	ShaderProgram();
	~ShaderProgram();

	void setModelMatrix(mat4 model);
	void setViewMatrix(mat4 view);
	void setProjectionMatrix(mat4 projection);
	void setTexture(GLuint texture_id);

	void loadShaders(string vertex_shader_filename, string fragment_shader_filename);
	void use();
};