#include "chunk.h"
#include <memory.h>

Chunk::Chunk()
{
	_block = new char[chunk_block_count];
	memset(_block, 0, chunk_block_count);

}

Chunk::~Chunk()
{
	delete[] _block;
}

void Chunk::setBlock(int x, int y, int z, BlockIndex index)
{
	_block[x + chunk_size_x * z + chunk_size_x * chunk_size_z * y] = index;
}