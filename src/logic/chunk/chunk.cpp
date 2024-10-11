#include "chunk.h"

Chunk::Chunk()
{
	_block = new char** [chunk_size_x];
	for (size_t x = 0; x < chunk_size_x; x++)
	{
		_block[x] = new char* [chunk_size_z];
		for (size_t z = 0; z < chunk_size_z; z++)
		{
			_block[x][z] = new char[chunk_size_y];
			memset(_block[x][z], BlockIndex::air, chunk_size_y);
		}
	}
}

Chunk::~Chunk()
{
	for (int x = 0; x < chunk_size_x; x++) {
		for (int z = 0; z < chunk_size_z; z++) {
			delete[] _block[x][z];   
		}
		delete[] _block[x];          
	}
	delete[] _block;                 
}

void Chunk::setBlock(BlockIndex block_type, int x, int z, int y)
{
	_block[x][z][y] = block_type;
}

char*** Chunk::getChunkData()
{
	return _block;
}