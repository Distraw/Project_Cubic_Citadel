#pragma once
#include "glad/glad.h"
#include "GLFW/glfw3.h"


class ChunkRenderer
{
private:
	GLuint _vao;
	GLuint _vertex_buffer;
	GLuint _texcoord_buffer;
	int _vertices_amount, _texcoord_amount;
public:
	ChunkRenderer();
	~ChunkRenderer();

	void init();

	void prepareChunk(char* chunk, float xpos, float zpos);
	void render();
};