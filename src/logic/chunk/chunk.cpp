#include "chunk.h"
#include <memory.h>

Chunk::Chunk()
{
	_block = new char**[chunk_size_x];

	memset(_block, 0, chunk_block_count);
}

Chunk::~Chunk()
{
	delete[] _block;
}

void Chunk::setBlock(int x, int y, int z, BlockId block_id)
{

}