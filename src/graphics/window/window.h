#pragma once
#include "glad/glad.h"
#include "GLFW/glfw3.h"
#include <string>

#include "glm/glm.hpp"
using namespace glm;

class Window
{
private:
	GLFWwindow* _window;

	int _width;
	int _height;
	std::string _title;
	GLFWmonitor* _screen;

	double _prev_frame_time;
	double _curr_frame_time;
	double _delta_time;
public:
	Window(int width, int height, std::string title, GLFWmonitor* screen);
	~Window();

	void init();
	void refresh();

	void setBackgroundColor(float red, float green, float blue);

	void hideCursor();
	void showCursor();

	bool isOpened();
	bool isKeyPressed(int key_id);

	void getCursorPos(double& xpos, double &ypos);

	int getWidth();
	int getHeight();
	double getDeltaTime();
	const double* getDeltaTimePtr();
	GLFWwindow* getWindowPtr();
};