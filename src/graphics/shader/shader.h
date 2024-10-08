#pragma once
#include "glad/glad.h"
#include "GLFW/glfw3.h"
#include <string>
using namespace std;

class Shader
{
private:
	string _source;

	GLuint _shader;
	GLenum _type;
public:
	Shader(GLenum type);
	~Shader();

	void load(string filename);

	GLuint getId();
};