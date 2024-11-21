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

void Chunk::raycastBlock(BlockIndex block_type, vec3 position, vec3 direction)
{
	vec3 current_position;
	ivec3 prev_block_pos;
	ivec3 block_pos = floor(position);
	for (float t = 0.f; t < MAX_RAY_DISTANCE; t += STEP_LENGTH)
	{
		current_position = position + t * direction;

		prev_block_pos = block_pos;
		block_pos = floor(current_position);

		if (_block[block_pos.x + block_pos.z * chunk_size_x + block_pos.y * chunk_size_x * chunk_size_z] 
			!= BlockIndex::air)
		{
			if (block_type != BlockIndex::air)
			{
				ivec3 offset_pos = block_pos - prev_block_pos;
				block_pos -= offset_pos;
			}
			
			setBlock(block_type, block_pos.x, block_pos.z, block_pos.y);

			return;
		}
	}
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