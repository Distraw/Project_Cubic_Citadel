#pragma once
#include "logic/chunk/chunk.h"
#include "graphics/render/chunk_render.h"

class World
{
private:
	Chunk* _chunk;
	ChunkRenderer* _renderer;

	GLuint _texture_atlas_id;

public:
	World();
	~World();

	void generate();
	void refreshBuffers();
	void render();

	void raycastBlock(BlockIndex block_type, vec3 position, vec3 direction);
	void setBlock(BlockIndex block, int x, int y, int z, bool refresh_chunk = true);
	void setTree(int x, int y, int z);

	BlockIndex getBlock(int x, int y, int z);

	void loadTextureAtlas(const char* filename);
	void bindTextureAtlas();
};