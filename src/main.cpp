#include "graphics/window/window.h"
#include "graphics/shader/program.h"
#include "logic/player/camera.h"
#include <stdexcept>

#include "glm/glm.hpp"
using namespace glm;

#ifdef _DEBUG
#include <iostream>
#endif

void processInput(Window& window, Camera& camera);

double prev_cursor_pos_x = 0;
double prev_cursor_pos_y = 0;

int main()
{
	Window window(600, 600, "Window", NULL);
	ShaderProgram program;
	Camera camera;

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
		0, 0.5, 1,
		-0.5, -0.5, 1,
		0.5, -0.5, 1
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

	camera.setDeltaTimePtr(window.getDeltaTimePtr());
	window.hideCursor();
	window.setBackgroundColor(0, 1, 1);
	while (window.isOpened())
	{
		window.refresh();

		processInput(window, camera);
		camera.update();

		mat4 model = mat4(1.0f);
		model = translate(model, vec3(0, 0.f, 0.f));

		program.setModelMatrix(model);
		program.setViewMatrix(camera.getViewMatrix());
		program.setProjectionMatrix(camera.getProjectionMatrix());

		glDrawArrays(GL_TRIANGLES, 0, 3);
	}

	return 0;
}

void processInput(Window& window, Camera& camera)
{
	double cursor_pos_x;
	double cursor_pos_y;

	window.getCursorPos(cursor_pos_x, cursor_pos_y);

	camera.rotate(cursor_pos_x - prev_cursor_pos_x, prev_cursor_pos_y - cursor_pos_y);
	prev_cursor_pos_x = cursor_pos_x;
	prev_cursor_pos_y = cursor_pos_y;

	if (window.isKeyPressed(GLFW_KEY_W))
	{
		camera.definedMove(0, 0, 1);
	}
	if (window.isKeyPressed(GLFW_KEY_S))
	{
		camera.definedMove(0, 0, -1);
	}
	if (window.isKeyPressed(GLFW_KEY_A))
	{
		camera.definedMove(-1, 0, 0);
	}
	if (window.isKeyPressed(GLFW_KEY_D))
	{
		camera.definedMove(1, 0, 0);
	}
	if (window.isKeyPressed(GLFW_KEY_SPACE))
	{
		camera.definedMove(0, 1, 0);
	}
	if (window.isKeyPressed(GLFW_KEY_LEFT_CONTROL))
	{
		camera.definedMove(0, -1, 0);
	}
}