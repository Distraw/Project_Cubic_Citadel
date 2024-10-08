#include "shader.h"
#include <fstream>
#include <sstream>

Shader::Shader(GLenum type)
	: _source(""), _shader(0), _type(type)
{

}

Shader::~Shader()
{
	if (_shader) glDeleteShader(_shader);
}

void Shader::load(string filename)
{
	ifstream file(filename);
	if (!file.is_open())
	{
		string error_message = "Shader source \'" + filename + "\' was not found";
		throw runtime_error(error_message);
	}

	stringstream buffer;
	buffer << file.rdbuf();
	_source = buffer.str();

	_shader = glCreateShader(_type);


	const char* cc_source = _source.c_str();
	glShaderSource(_shader, 1, &cc_source, nullptr);
	glCompileShader(_shader);

	int ok;
	glGetShaderiv(_shader, GL_COMPILE_STATUS, &ok);
	if (!ok)
	{
		char infolog[1024];
		glGetShaderInfoLog(_shader, 1024, NULL, infolog);
		throw runtime_error(string(infolog));
	}
}

GLuint Shader::getId()
{
	return _shader;
}