#pragma once
#include "glad/glad.h"
#include "GLFW/glfw3.h"
#include <string>

class Window
{
private:
	GLFWwindow* _window;

	int _width;
	int _height;
	std::string _title;
	GLFWmonitor* _screen;
public:
	Window(int width, int height, std::string title, GLFWmonitor* screen);
	~Window();

	void init();
	void refresh();

	void setBackgroundColor(float red, float green, float blue);

	bool isOpened();

	int getWidth();
	int getHeight();
	GLFWwindow* getWindowPtr();
};