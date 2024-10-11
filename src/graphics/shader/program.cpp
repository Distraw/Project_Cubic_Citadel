#include "program.h"
#include <stdexcept>

ShaderProgram::ShaderProgram()
{

}

ShaderProgram::~ShaderProgram()
{
	if (!_program) glDeleteProgram(_program);
}

void ShaderProgram::setViewMatrix(mat4 view_matrix)
{
	glUniformMatrix4fv(glGetUniformLocation(_program, "view"), 1, GL_FALSE, &view_matrix[0][0]);
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
}

void ShaderProgram::use()
{
	glUseProgram(_program);
}