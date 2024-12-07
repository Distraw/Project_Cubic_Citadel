#include "chunk.h"

Chunk::Chunk()
{
	_block = new char[chunk_total_block_amount];
	memset(_block, 0, chunk_total_block_amount * sizeof(char));
}

Chunk::~Chunk()
{
	delete[] _block;                 
}

void Chunk::setBlock(BlockIndex block_type, int x, int z, int y)
{
	if (x >= chunk_size_x || z >= chunk_size_z || y >= chunk_size_y
		|| x < 0 || z < 0 || y < 0)
		return;

	_block[x + z * chunk_size_x + y * chunk_size_x * chunk_size_z] = block_type;
}

BlockIndex Chunk::getBlock(int x, int y, int z)
{
	return BlockIndex(_block[x + z * chunk_size_x + y * chunk_size_x * chunk_size_z]);
}

char* Chunk::getChunkData()
{
	return _block;
}