#pragma once
#include <iostream>
#include <glm/glm.hpp>
#include "block_definition.h"
using namespace glm;
using namespace std;

constexpr float MAX_RAY_DISTANCE = 100.f;
constexpr float STEP_LENGTH = 0.1f;

constexpr int chunk_size_x = 16;
constexpr int chunk_size_z = 16;
constexpr int chunk_size_y = 64;
constexpr int chunk_total_block_amount = chunk_size_x * chunk_size_y * chunk_size_z;

class Chunk 
{
private:
	char* _block;
public:
	Chunk();
	~Chunk();

	void raycastBlock(BlockIndex block_type, vec3 position, vec3 direction);
	void setBlock(BlockIndex block_type, int x, int z, int y);

	BlockIndex getBlock(int x, int y, int z);
	char* getChunkData();
};