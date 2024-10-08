#include "graphics/window/window.h"
#include "graphics/shader/program.h"
#include <stdexcept>

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
	}
	catch (const exception& ex)
	{
#ifdef _DEBUG
		std::cout << ex.what() << endl;
#endif
		return -1;
	}

	window.setBackgroundColor(0, 0, 1);
	while (window.isOpened())
	{
		window.refresh();
	}

	return 0;
}

//#include <glad/glad.h>
//#include <GLFW/glfw3.h>
//
//int main()
//{
//	glfwInit();
//	GLFWwindow* window = glfwCreateWindow(600, 600, "asd", 0, 0);
//	glfwMakeContextCurrent(window);
//	gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
//
//	glClearColor(1, 1, 1, 1);
//	while (!glfwWindowShouldClose(window))
//	{
//		glfwPollEvents();
//		glClear(GL_COLOR_BUFFER_BIT);
//		glfwSwapBuffers(window);
//	}
//
//	return 0;
//}