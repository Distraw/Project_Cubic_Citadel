/*
	Minecraft clone made by Karazin University KS13 group
	to get 100 diamonds in a competition :)

	 Language: C++, GLSL (for shaders)
	 Used external libraries/headers:
	 1) Opengl					: opengl32.lib
	 2) GLFW					: glfw3.lib, glfw3.h
	 3) STB image loader		: stb_image.h
	 4) GLAD (OpenGL loader)	: glad.c
	 5) Nlohmann (JSON parser)	: json.hpp

	 Created on Visual Studio 2022
	 
	 Windows only, but code is "mostly" written
	 to work on different platforms

	 Code by Dima and Nikita
	 2024
*/ 

#include "graphics/window/window.h"
#include "graphics/shader/program.h"
#include "logic/player/camera.h"
#include "world/world.h"

#include <stdexcept>
#include "glm/glm.hpp"
using namespace glm;

#ifdef _DEBUG
#include <iostream>
#endif

void processInput();

double prev_cursor_pos_x = 0;
double prev_cursor_pos_y = 0;

bool is_lmb_pressed = false;
bool is_rmb_pressed = false;
BlockIndex active_block = BlockIndex::dirt;

Window window(1000, 1000, "Window", NULL);
ShaderProgram program;
Camera camera;
World world;

int main()
{
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

	program.setTexture(0);

	world.generate();
	world.loadTextureAtlas("texture//atlas.jpg");

	camera.setDeltaTimePtr(window.getDeltaTimePtr());
	window.hideCursor();
	window.setBackgroundColor(0, 1, 1);
	while (window.isOpened())
	{
		window.refresh();

		processInput();
		camera.update();

		mat4 model = mat4(1.0f);
		model = translate(model, vec3(0, 0.f, 0.f));

		program.setModelMatrix(model);
		program.setViewMatrix(camera.getViewMatrix());
		program.setProjectionMatrix(camera.getProjectionMatrix());

		world.bindTextureAtlas();
		program.setTexture(0);
		world.render();
	}

	return 0;
}

void processInput()
{
	double cursor_pos_x;
	double cursor_pos_y;

	window.getCursorPos(cursor_pos_x, cursor_pos_y);

	camera.rotate(cursor_pos_x - prev_cursor_pos_x, prev_cursor_pos_y - cursor_pos_y);
	prev_cursor_pos_x = cursor_pos_x;
	prev_cursor_pos_y = cursor_pos_y;

	if (window.isMouseButtonPressed(GLFW_MOUSE_BUTTON_RIGHT))
	{
		if (is_rmb_pressed == false)
		{
			is_rmb_pressed = true;
			world.raycastBlock(active_block, camera.getPosition(), camera.getFrontVector());
		}
	}
	else is_rmb_pressed = false;

	if (window.isMouseButtonPressed(GLFW_MOUSE_BUTTON_LEFT))
	{
		if (is_lmb_pressed == false)
		{
			is_lmb_pressed = true;
			world.raycastBlock(BlockIndex::air, camera.getPosition(), camera.getFrontVector());
		}
	}
	else is_lmb_pressed = false;

	if (window.isKeyPressed(GLFW_KEY_1))
	{
		active_block = BlockIndex::dirt;
	}
	if (window.isKeyPressed(GLFW_KEY_2))
	{
		active_block = BlockIndex::grass;
	}
	if (window.isKeyPressed(GLFW_KEY_3))
	{
		active_block = BlockIndex::stone;
	}
	if (window.isKeyPressed(GLFW_KEY_4))
	{
		active_block = BlockIndex::bedrock;
	}
	if (window.isKeyPressed(GLFW_KEY_5))
	{
		active_block = BlockIndex::cobblestone;
	}
	if (window.isKeyPressed(GLFW_KEY_6))
	{
		active_block = BlockIndex::sand;
	}
	if (window.isKeyPressed(GLFW_KEY_7))
	{
		active_block = BlockIndex::planks;
	}
	if (window.isKeyPressed(GLFW_KEY_8))
	{
		active_block = BlockIndex::wood;
	}
	if (window.isKeyPressed(GLFW_KEY_9))
	{
		active_block = BlockIndex::leaves;
	}

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