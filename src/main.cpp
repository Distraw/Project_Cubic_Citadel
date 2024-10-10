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

	window.setBackgroundColor(0, 1, 1);
	while (window.isOpened())
	{
		window.refresh();
	}

	return 0;
}