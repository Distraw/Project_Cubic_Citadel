#include "window.h"
#include <stdexcept>

Window::Window(int width, int height, std::string title, GLFWmonitor* screen)
	: _width(width), _height(height), _title(title), _screen(screen), _window(nullptr)
{
	
}

Window::~Window()
{
	if (_window) glfwDestroyWindow(_window);
	glfwTerminate();
}

// Throws exception if GLFW or GLAD were not initialized
void Window::init()
{
	if (!glfwInit()) throw std::runtime_error("GLFW was not initialized");
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
		
	_window = glfwCreateWindow(_width, _height, _title.c_str(), _screen, NULL);
	if (!_window) throw std::runtime_error("Window failed to open");
	glfwMakeContextCurrent(_window);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) throw std::runtime_error("GLAD was not initialized");
}

void Window::refresh()
{
	glfwPollEvents();
	glfwSwapBuffers(_window);
	glClear(GL_COLOR_BUFFER_BIT);
}

void Window::setBackgroundColor(float red, float green, float blue)
{
	glClearColor(red, green, blue, 0);
}

bool Window::isOpened()
{
	return !glfwWindowShouldClose(_window);
}

int Window::getWidth()
{
	return _width;
}

int Window::getHeight()
{
	return _height;
}

GLFWwindow* Window::getWindowPtr()
{
	return _window;
}