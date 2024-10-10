#pragma once
#include "block_definition.h"
constexpr int chunk_size_x = 16;
constexpr int chunk_size_z = 16;
constexpr int chunk_size_y = 64;
constexpr int chunk_block_count = chunk_size_x * chunk_size_y * chunk_size_z;

class Chunk
{
private:
	char* _block;
public:
	Chunk();
	~Chunk();

	void setBlock(int x, int y, int z, BlockIndex index);
};