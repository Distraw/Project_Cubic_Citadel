#include "graphics/window/window.h"
#include "graphics/shader/program.h"
#include <stdexcept>

#include "glm/glm.hpp"
using namespace glm;

#ifdef _DEBUG
#include <iostream>
#endif

int main()
{
	Window window(600, 600, "Window", NULL);
	ShaderProgram program;

	try
	{
		window.init();
		program.loadShaders("shader_source//default_vertex_shader.glsl",
			"shader_source//default_fragment_shader.glsl");
		program.use();
	}
	catch (const exception& ex)
	{
#ifdef _DEBUG
		std::cout << ex.what() << endl;
#endif
		return -1;
	}

	float vertices[] =
	{
		0, 0.5, 0,
		-0.5, -0.5, 0,
		0.5, -0.5, 0
	};

	unsigned int VAO;
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);
	unsigned int VBO;
	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	window.setBackgroundColor(0, 1, 1);
	while (window.isOpened())
	{
		window.refresh();

		glDrawArrays(GL_TRIANGLES, 0, 3);
	}

	return 0;
}