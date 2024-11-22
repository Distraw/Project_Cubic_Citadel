#include "window.h"
#include <stdexcept>
#include <chrono>
#include <thread>

constexpr double target_frame_time = 1.0f / 120.0f;

Window::Window(int width, int height, std::string title, GLFWmonitor* screen)
	: _width(width), _height(height), _title(title), _screen(screen), _window(nullptr),
	_prev_frame_time(0), _curr_frame_time(0), _delta_time(0)
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
	glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
		
	_window = glfwCreateWindow(_width, _height, _title.c_str(), _screen, NULL);
	if (!_window) throw std::runtime_error("Window failed to open");
	glfwMakeContextCurrent(_window);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) throw std::runtime_error("GLAD was not initialized");

	glEnable(GL_DEPTH_TEST);
}

void Window::refresh()
{
	_prev_frame_time = _curr_frame_time;
	_curr_frame_time = glfwGetTime();
	_delta_time = _curr_frame_time - _prev_frame_time;

	double sleep_time = target_frame_time - _delta_time;
	std::this_thread::sleep_for(std::chrono::duration<double>(sleep_time));

	glfwPollEvents();
	glfwSwapBuffers(_window);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Window::close()
{
	glfwSetWindowShouldClose(_window, true);
}

void Window::setBackgroundColor(float red, float green, float blue)
{
	glClearColor(red, green, blue, 0);
}

void Window::hideCursor()
{
	glfwSetInputMode(_window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
}

void Window::showCursor()
{
	glfwSetInputMode(_window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
}

bool Window::isOpened()
{
	return !glfwWindowShouldClose(_window);
}

bool Window::isKeyPressed(int key_id)
{
	return glfwGetKey(_window, key_id) == GLFW_PRESS;
}

bool Window::isMouseButtonPressed(int key_id)
{
	return glfwGetMouseButton(_window, key_id) == GLFW_PRESS;
}

void Window::getCursorPos(double& xpos, double& ypos)
{
	glfwGetCursorPos(_window, &xpos, &ypos);
}

int Window::getWidth()
{
	return _width;
}

int Window::getHeight()
{
	return _height;
}

double Window::getDeltaTime()
{
	return _delta_time;
}

const double* Window::getDeltaTimePtr()
{
	return &_delta_time;
}

GLFWwindow* Window::getWindowPtr()
{
	return _window;
}