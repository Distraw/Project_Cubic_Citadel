#pragma once
#include <iostream>
#include "block_definition.h"
using namespace std;

constexpr int chunk_size_x = 16;
constexpr int chunk_size_z = 16;
constexpr int chunk_size_y = 64;

class Chunk 
{
private:
	char*** _block;
public:
	Chunk();
	~Chunk();
	void setBlock(BlockIndex block_type,int x,int z,int y);
	char*** getChunkData();
};