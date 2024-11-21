#include "program.h"
#include <stdexcept>

ShaderProgram::ShaderProgram()
{

}

ShaderProgram::~ShaderProgram()
{
	if (!_program) glDeleteProgram(_program);
}

void ShaderProgram::setModelMatrix(mat4 model)
{
	glUniformMatrix4fv(_model_location, 1, GL_FALSE, &model[0][0]);
}

void ShaderProgram::setViewMatrix(mat4 view)
{
	glUniformMatrix4fv(_view_location, 1, GL_FALSE, &view[0][0]);
}

void ShaderProgram::setProjectionMatrix(mat4 projection)
{
	glUniformMatrix4fv(_projection_location, 1, GL_FALSE, &projection[0][0]);
}

void ShaderProgram::setTexture(GLuint texture_id)
{
	glUniform1i(_texture_location, texture_id);
}

void ShaderProgram::loadShaders(string vertex_shader_filename, string fragment_shader_filename)
{
	Shader vertex_shader(GL_VERTEX_SHADER);
	Shader fragment_shader(GL_FRAGMENT_SHADER);

	vertex_shader.load(vertex_shader_filename);
	fragment_shader.load(fragment_shader_filename);

	_program = glCreateProgram();
	glUseProgram(_program);
	glAttachShader(_program, vertex_shader.getId());
	glAttachShader(_program, fragment_shader.getId());

	glLinkProgram(_program);

	int ok;
	glGetProgramiv(_program, GL_LINK_STATUS, &ok);
	if (!ok)
	{
		char infolog[1024];
		glGetProgramInfoLog(_program, 1024, NULL, infolog);
		throw runtime_error(string(infolog));
	}

	_model_location			= glGetUniformLocation(_program, "model");
	_view_location			= glGetUniformLocation(_program, "view");
	_projection_location	= glGetUniformLocation(_program, "projection");
	_texture_location		= glGetUniformLocation(_program, "texture_atlas");
}

void ShaderProgram::use()
{
	glUseProgram(_program);
}