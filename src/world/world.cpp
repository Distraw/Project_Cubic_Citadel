#include "world.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

void World::generate()
{
	_chunk = new Chunk[64];
	_renderer = new ChunkRenderer[64];

	for (int i = 0; i < 8; i++)
	{
		for (int k = 0; k < 8; k++)
		{
			for (int j = 0; j < 16; j++)
				for (int g = 0; g < 16; g++)
				{
					_chunk[i * 8 + k].setBlock(BlockIndex::stone, j, g, 0);
					_chunk[i * 8 + k].setBlock(BlockIndex::stone, j, g, 1);
					_chunk[i * 8 + k].setBlock(BlockIndex::stone, j, g, 2);
					_chunk[i * 8 + k].setBlock(BlockIndex::stone, j, g, 3);
					_chunk[i * 8 + k].setBlock(BlockIndex::dirt, j, g, 4);
					_chunk[i * 8 + k].setBlock(BlockIndex::dirt, j, g, 5);
					_chunk[i * 8 + k].setBlock(BlockIndex::grass, j, g, 6);
				}

			_renderer[i * 8 + k].init();
			_renderer[i * 8 + k].prepareChunk(_chunk[i * 8 + k].getChunkData(), i * 16, k * 16);
		}
	}
}

void World::render()
{
	for (int i = 0; i < 64; i++)
	{
		_renderer[i].render();
	}
}

void World::raycastBlock(BlockIndex block_type, vec3 position, vec3 direction)
{
	if (position.x < 0 || position.y < 0 || position.z < 0 || position.x > 128 || 
		position.y > 64 || position.z > 128) return;

	vec3 current_position;
	ivec3 prev_block_pos;
	ivec3 block_pos = floor(position);
	for (float t = 0.f; t < MAX_RAY_DISTANCE; t += STEP_LENGTH)
	{
		current_position = position + t * direction;

		prev_block_pos = block_pos;
		block_pos = floor(current_position);

		if (block_pos.x < 0 || block_pos.y < 0 || block_pos.z < 0 ||
			block_pos.x > 128 || block_pos.y > 64 || block_pos.z > 128)
			return;

		if (_chunk[block_pos.x / 16 * 8 + block_pos.z / 16].getBlock(block_pos.x % 16, block_pos.y, block_pos.z % 16)
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

void World::setBlock(BlockIndex block, int x, int z, int y)
{
	if (x < 0 || y < 0 || z < 0 || x > 128 || y > 64 || z > 128) return;

	int x_index = x / 16;
	int z_index = z / 16;

	_chunk[x_index * 8 + z_index].setBlock(block, x % 16, z % 16, y);
	_renderer[x_index * 8 + z_index].prepareChunk(_chunk[x_index * 8 + z_index].getChunkData(), x_index * 16, z_index * 16);
}

BlockIndex World::getBlock(int x, int y, int z)
{
	if (x < 0 || y < 0 || z < 0 || x > 128 || y > 64 || z > 128) return BlockIndex::air;

	int x_index = x / 16;
	int z_index = z / 16;

	return BlockIndex(_chunk[x_index * 8 + z_index].getBlock(x % 16, y, z % 16));
}

void World::loadTextureAtlas(const char* filename)
{
	int width, height, nr_channels;
	unsigned char* texture_source = stbi_load(filename, &width, &height, &nr_channels, 0);
	if (!texture_source)
	{
		stbi_image_free(texture_source);
		throw runtime_error("Texture atlas file was not found");
	}

	glGenTextures(1, &_texture_atlas_id);
	glBindTexture(GL_TEXTURE_2D, _texture_atlas_id);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	glTexImage2D(GL_TEXTURE_2D, 0, nr_channels == 3 ? GL_RGB : GL_RGBA, width, height,
		0, nr_channels == 3 ? GL_RGB : GL_RGBA, GL_UNSIGNED_BYTE, texture_source);
	glGenerateMipmap(GL_TEXTURE_2D);
}

void World::bindTextureAtlas()
{
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, _texture_atlas_id);
}