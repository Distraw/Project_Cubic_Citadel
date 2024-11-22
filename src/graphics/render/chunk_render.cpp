#include "chunk_render.h"
#include "block_definition.h"

#include <iostream>
using namespace std;

ChunkRenderer::ChunkRenderer()
{
	
}

ChunkRenderer::~ChunkRenderer()
{

}

void ChunkRenderer::init()
{
	glGenVertexArrays(1, &_vao);
	glGenBuffers(1, &_vertex_buffer);
	glGenBuffers(1, &_texcoord_buffer);
}

// This method is bullshit, but I don`t know how to make it better :)
void ChunkRenderer::prepareChunk(char* chunk, float xpos, float zpos)
{
	float* vertex_buffer = new float[3 * 3 * 2 * 6 * 16 * 16 * 64];
	float* texcoord_buffer = new float[2 * 3 * 2 * 6 * 16 * 16 * 64];
	memset(vertex_buffer, 0, 3 * 3 * 2 * 6 * 16 * 16 * 64 * sizeof(float));
	memset(texcoord_buffer, 0, 2 * 3 * 2 * 6 * 16 * 16 * 64 * sizeof(float));

	float face_texcoord_buffer[24];
	_vertices_amount = 0;
	_texcoord_amount = 0;
	for (size_t x = 0; x < 16; x++)
	{
		for (size_t z = 0; z < 16; z++)
		{
			for (size_t y = 0; y < 64; y++)
			{
				float bx_pos = x + xpos;
				float bz_pos = z + zpos;

				switch (chunk[x + z * 16 + y * 16 * 16])
				{
				case 0:
					continue;
				case 1:
					face_texcoord_buffer[0] = 0.f;
					face_texcoord_buffer[1] = 0.f;

					face_texcoord_buffer[2] = 0.125f;
					face_texcoord_buffer[3] = 0.f;

					face_texcoord_buffer[4] = 0.125f;
					face_texcoord_buffer[5] = 0.125f;

					face_texcoord_buffer[6] = 0.f;
					face_texcoord_buffer[7] = 0.125f;


					face_texcoord_buffer[8] = 0.125f;
					face_texcoord_buffer[9] = 0.125f;

					face_texcoord_buffer[10] = 0.25f;
					face_texcoord_buffer[11] = 0.125f;

					face_texcoord_buffer[12] = 0.25f;
					face_texcoord_buffer[13] = 0.0f;

					face_texcoord_buffer[14] = 0.125f;
					face_texcoord_buffer[15] = 0.0f;


					face_texcoord_buffer[16] = 0.25f;
					face_texcoord_buffer[17] = 0.f;

					face_texcoord_buffer[18] = 0.375f;
					face_texcoord_buffer[19] = 0.f;

					face_texcoord_buffer[20] = 0.375f;
					face_texcoord_buffer[21] = 0.125f;

					face_texcoord_buffer[22] = 0.25f;
					face_texcoord_buffer[23] = 0.125f;
					break;

				case 2:
					face_texcoord_buffer[0] = 0.25f;
					face_texcoord_buffer[1] = 0.f;
					face_texcoord_buffer[8] = 0.25f;
					face_texcoord_buffer[9] = 0.f;
					face_texcoord_buffer[16] = 0.25f;
					face_texcoord_buffer[17] = 0.f;

					face_texcoord_buffer[2] = 0.375f;
					face_texcoord_buffer[3] = 0.f;
					face_texcoord_buffer[10] = 0.375f;
					face_texcoord_buffer[11] = 0.f;
					face_texcoord_buffer[18] = 0.375f;
					face_texcoord_buffer[19] = 0.f;

					face_texcoord_buffer[4] = 0.375f;
					face_texcoord_buffer[5] = 0.125f;
					face_texcoord_buffer[12] = 0.375f;
					face_texcoord_buffer[13] = 0.125f;
					face_texcoord_buffer[20] = 0.375f;
					face_texcoord_buffer[21] = 0.125f;

					face_texcoord_buffer[6] = 0.25f;
					face_texcoord_buffer[7] = 0.125f;
					face_texcoord_buffer[14] = 0.25f;
					face_texcoord_buffer[15] = 0.125f;
					face_texcoord_buffer[22] = 0.25f;
					face_texcoord_buffer[23] = 0.125f;
					break;

				case 3:
					face_texcoord_buffer[0] = 0.375f;
					face_texcoord_buffer[1] = 0.f;
					face_texcoord_buffer[8] = 0.375f;
					face_texcoord_buffer[9] = 0.f;
					face_texcoord_buffer[16] = 0.375f;
					face_texcoord_buffer[17] = 0.f;

					face_texcoord_buffer[2] = 0.5f;
					face_texcoord_buffer[3] = 0.f;
					face_texcoord_buffer[10] = 0.5f;
					face_texcoord_buffer[11] = 0.f;
					face_texcoord_buffer[18] = 0.5f;
					face_texcoord_buffer[19] = 0.f;

					face_texcoord_buffer[4] = 0.5f;
					face_texcoord_buffer[5] = 0.125f;
					face_texcoord_buffer[12] = 0.5f;
					face_texcoord_buffer[13] = 0.125f;
					face_texcoord_buffer[20] = 0.5f;
					face_texcoord_buffer[21] = 0.125f;

					face_texcoord_buffer[6] = 0.375f;
					face_texcoord_buffer[7] = 0.125f;
					face_texcoord_buffer[14] = 0.375f;
					face_texcoord_buffer[15] = 0.125f;
					face_texcoord_buffer[22] = 0.375f;
					face_texcoord_buffer[23] = 0.125f;
					break;

				case 4:
					face_texcoord_buffer[0] = 0.5f;
					face_texcoord_buffer[1] = 0.f;
					face_texcoord_buffer[8] = 0.5f;
					face_texcoord_buffer[9] = 0.f;
					face_texcoord_buffer[16] = 0.5f;
					face_texcoord_buffer[17] = 0.f;

					face_texcoord_buffer[2] = 0.625f;
					face_texcoord_buffer[3] = 0.f;
					face_texcoord_buffer[10] = 0.625f;
					face_texcoord_buffer[11] = 0.f;
					face_texcoord_buffer[18] = 0.625f;
					face_texcoord_buffer[19] = 0.f;

					face_texcoord_buffer[4] = 0.625f;
					face_texcoord_buffer[5] = 0.125f;
					face_texcoord_buffer[12] = 0.625f;
					face_texcoord_buffer[13] = 0.125f;
					face_texcoord_buffer[20] = 0.625f;
					face_texcoord_buffer[21] = 0.125f;

					face_texcoord_buffer[6] = 0.5f;
					face_texcoord_buffer[7] = 0.125f;
					face_texcoord_buffer[14] = 0.5f;
					face_texcoord_buffer[15] = 0.125f;
					face_texcoord_buffer[22] = 0.5f;
					face_texcoord_buffer[23] = 0.125f;
					break;
				case 5:
					face_texcoord_buffer[0] = 0.625f;
					face_texcoord_buffer[1] = 0.f;
					face_texcoord_buffer[8] = 0.625f;
					face_texcoord_buffer[9] = 0.f;
					face_texcoord_buffer[16] = 0.625f;
					face_texcoord_buffer[17] = 0.f;

					face_texcoord_buffer[2] = 0.75f;
					face_texcoord_buffer[3] = 0.f;
					face_texcoord_buffer[10] = 0.75f;
					face_texcoord_buffer[11] = 0.f;
					face_texcoord_buffer[18] = 0.75f;
					face_texcoord_buffer[19] = 0.f;

					face_texcoord_buffer[4] = 0.75f;
					face_texcoord_buffer[5] = 0.125f;
					face_texcoord_buffer[12] = 0.75f;
					face_texcoord_buffer[13] = 0.125f;
					face_texcoord_buffer[20] = 0.75f;
					face_texcoord_buffer[21] = 0.125f;

					face_texcoord_buffer[6] = 0.625f;
					face_texcoord_buffer[7] = 0.125f;
					face_texcoord_buffer[14] = 0.625f;
					face_texcoord_buffer[15] = 0.125f;
					face_texcoord_buffer[22] = 0.625f;
					face_texcoord_buffer[23] = 0.125f;
					break;
				case 6:
					face_texcoord_buffer[0] = 0.75f;
					face_texcoord_buffer[1] = 0.f;
					face_texcoord_buffer[8] = 0.75f;
					face_texcoord_buffer[9] = 0.f;
					face_texcoord_buffer[16] = 0.75f;
					face_texcoord_buffer[17] = 0.f;

					face_texcoord_buffer[2] = 0.875f;
					face_texcoord_buffer[3] = 0.f;
					face_texcoord_buffer[10] = 0.875f;
					face_texcoord_buffer[11] = 0.f;
					face_texcoord_buffer[18] = 0.875f;
					face_texcoord_buffer[19] = 0.f;

					face_texcoord_buffer[4] = 0.875f;
					face_texcoord_buffer[5] = 0.125f;
					face_texcoord_buffer[12] = 0.875f;
					face_texcoord_buffer[13] = 0.125f;
					face_texcoord_buffer[20] = 0.875f;
					face_texcoord_buffer[21] = 0.125f;

					face_texcoord_buffer[6] = 0.75f;
					face_texcoord_buffer[7] = 0.125f;
					face_texcoord_buffer[14] = 0.75f;
					face_texcoord_buffer[15] = 0.125f;
					face_texcoord_buffer[22] = 0.75f;
					face_texcoord_buffer[23] = 0.125f;
					break;
				case 7:
					face_texcoord_buffer[0] = 0.875f;
					face_texcoord_buffer[1] = 0.f;
					face_texcoord_buffer[8] = 0.875f;
					face_texcoord_buffer[9] = 0.f;
					face_texcoord_buffer[16] = 0.875f;
					face_texcoord_buffer[17] = 0.f;

					face_texcoord_buffer[2] = 0.875f;
					face_texcoord_buffer[3] = 0.125f;
					face_texcoord_buffer[10] = 0.875f;
					face_texcoord_buffer[11] = 0.125f;
					face_texcoord_buffer[18] = 0.875f;
					face_texcoord_buffer[19] = 0.125f;

					face_texcoord_buffer[4] = 1.0f;
					face_texcoord_buffer[5] = 0.125f;
					face_texcoord_buffer[12] = 1.0f;
					face_texcoord_buffer[13] = 0.125f;
					face_texcoord_buffer[20] = 1.0f;
					face_texcoord_buffer[21] = 0.125f;

					face_texcoord_buffer[6] = 1.f;
					face_texcoord_buffer[7] = 0.f;
					face_texcoord_buffer[14] = 1.f;
					face_texcoord_buffer[15] = 0.f;
					face_texcoord_buffer[22] = 1.f;
					face_texcoord_buffer[23] = 0.f;
					break;
				case 8:
					face_texcoord_buffer[0] = 0.125f;
					face_texcoord_buffer[1] = 0.125f;

					face_texcoord_buffer[2] = 0.25f;
					face_texcoord_buffer[3] = 0.125f;

					face_texcoord_buffer[4] = 0.25f;
					face_texcoord_buffer[5] = 0.25f;

					face_texcoord_buffer[6] = 0.125f;
					face_texcoord_buffer[7] = 0.25f;


					face_texcoord_buffer[8] = 0.0f;
					face_texcoord_buffer[9] = 0.125f;

					face_texcoord_buffer[10] = 0.0f;
					face_texcoord_buffer[11] = 0.25f;

					face_texcoord_buffer[12] = 0.125f;
					face_texcoord_buffer[13] = 0.25f;

					face_texcoord_buffer[14] = 0.125f;
					face_texcoord_buffer[15] = 0.125f;


					face_texcoord_buffer[16] = 0.125f;
					face_texcoord_buffer[17] = 0.125f;

					face_texcoord_buffer[18] = 0.25f;
					face_texcoord_buffer[19] = 0.125f;

					face_texcoord_buffer[20] = 0.25f;
					face_texcoord_buffer[21] = 0.25f;

					face_texcoord_buffer[22] = 0.125f;
					face_texcoord_buffer[23] = 0.25f;
					break;
				case 9: 
					face_texcoord_buffer[0] = 0.25f;
					face_texcoord_buffer[1] = 0.125f;
					face_texcoord_buffer[8] = 0.25f;
					face_texcoord_buffer[9] = 0.125f;
					face_texcoord_buffer[16] = 0.25f;
					face_texcoord_buffer[17] = 0.125f;

					face_texcoord_buffer[2] = 0.375f;
					face_texcoord_buffer[3] = 0.125f;
					face_texcoord_buffer[10] = 0.375;
					face_texcoord_buffer[11] = 0.125f;
					face_texcoord_buffer[18] = 0.375;
					face_texcoord_buffer[19] = 0.125f;

					face_texcoord_buffer[4] = 0.375f;
					face_texcoord_buffer[5] = 0.25f;
					face_texcoord_buffer[12] = 0.375f;
					face_texcoord_buffer[13] = 0.25f;
					face_texcoord_buffer[20] = 0.375f;
					face_texcoord_buffer[21] = 0.25f;

					face_texcoord_buffer[6] = 0.25f;
					face_texcoord_buffer[7] = 0.25f;
					face_texcoord_buffer[14] = 0.25f;
					face_texcoord_buffer[15] = 0.25f;
					face_texcoord_buffer[22] = 0.25f;
					face_texcoord_buffer[23] = 0.25f;
					break;
				}

				if (z == 0 || chunk[x + (z - 1) * 16 + y * 16 * 16] == BlockIndex::air)
				{
					vertex_buffer[_vertices_amount + 0] = bx_pos;
					vertex_buffer[_vertices_amount + 1] = y;
					vertex_buffer[_vertices_amount + 2] = bz_pos;
					
					vertex_buffer[_vertices_amount + 3] = bx_pos + 1;
					vertex_buffer[_vertices_amount + 4] = y;
					vertex_buffer[_vertices_amount + 5] = bz_pos;

					vertex_buffer[_vertices_amount + 6] = bx_pos + 1;
					vertex_buffer[_vertices_amount + 7] = y + 1;
					vertex_buffer[_vertices_amount + 8] = bz_pos;

					vertex_buffer[_vertices_amount + 9] = bx_pos;
					vertex_buffer[_vertices_amount + 10] = y;
					vertex_buffer[_vertices_amount + 11] = bz_pos;

					vertex_buffer[_vertices_amount + 12] = bx_pos;
					vertex_buffer[_vertices_amount + 13] = y + 1;
					vertex_buffer[_vertices_amount + 14] = bz_pos;

					vertex_buffer[_vertices_amount + 15] = bx_pos + 1;
					vertex_buffer[_vertices_amount + 16] = y + 1;
					vertex_buffer[_vertices_amount + 17] = bz_pos;
					

					texcoord_buffer[_texcoord_amount + 0] = face_texcoord_buffer[8];
					texcoord_buffer[_texcoord_amount + 1] = face_texcoord_buffer[9];

					texcoord_buffer[_texcoord_amount + 2] = face_texcoord_buffer[10];
					texcoord_buffer[_texcoord_amount + 3] = face_texcoord_buffer[11];

					texcoord_buffer[_texcoord_amount + 4] = face_texcoord_buffer[12];
					texcoord_buffer[_texcoord_amount + 5] = face_texcoord_buffer[13];

					texcoord_buffer[_texcoord_amount + 6] = face_texcoord_buffer[8];
					texcoord_buffer[_texcoord_amount + 7] = face_texcoord_buffer[9];

					texcoord_buffer[_texcoord_amount + 8] = face_texcoord_buffer[14];
					texcoord_buffer[_texcoord_amount + 9] = face_texcoord_buffer[15];

					texcoord_buffer[_texcoord_amount + 10] = face_texcoord_buffer[12];
					texcoord_buffer[_texcoord_amount + 11] = face_texcoord_buffer[13];

					_texcoord_amount += 12;
					_vertices_amount += 18;
				}

				if (x == 15 || chunk[(x + 1) + z * 16 + y * 16 * 16] == BlockIndex::air)
				{
					vertex_buffer[_vertices_amount + 0] = bx_pos + 1;
					vertex_buffer[_vertices_amount + 1] = y;
					vertex_buffer[_vertices_amount + 2] = bz_pos;

					vertex_buffer[_vertices_amount + 3] = bx_pos + 1;
					vertex_buffer[_vertices_amount + 4] = y;
					vertex_buffer[_vertices_amount + 5] = bz_pos + 1;

					vertex_buffer[_vertices_amount + 6] = bx_pos + 1;
					vertex_buffer[_vertices_amount + 7] = y + 1;
					vertex_buffer[_vertices_amount + 8] = bz_pos + 1;

					vertex_buffer[_vertices_amount + 9] = bx_pos + 1;
					vertex_buffer[_vertices_amount + 10] = y;
					vertex_buffer[_vertices_amount + 11] = bz_pos;

					vertex_buffer[_vertices_amount + 12] = bx_pos + 1;
					vertex_buffer[_vertices_amount + 13] = y + 1;
					vertex_buffer[_vertices_amount + 14] = bz_pos;

					vertex_buffer[_vertices_amount + 15] = bx_pos + 1;
					vertex_buffer[_vertices_amount + 16] = y + 1;
					vertex_buffer[_vertices_amount + 17] = bz_pos + 1;


					texcoord_buffer[_texcoord_amount + 0] = face_texcoord_buffer[8];
					texcoord_buffer[_texcoord_amount + 1] = face_texcoord_buffer[9];

					texcoord_buffer[_texcoord_amount + 2] = face_texcoord_buffer[10];
					texcoord_buffer[_texcoord_amount + 3] = face_texcoord_buffer[11];

					texcoord_buffer[_texcoord_amount + 4] = face_texcoord_buffer[12];
					texcoord_buffer[_texcoord_amount + 5] = face_texcoord_buffer[13];

					texcoord_buffer[_texcoord_amount + 6] = face_texcoord_buffer[8];
					texcoord_buffer[_texcoord_amount + 7] = face_texcoord_buffer[9];

					texcoord_buffer[_texcoord_amount + 8] = face_texcoord_buffer[14];
					texcoord_buffer[_texcoord_amount + 9] = face_texcoord_buffer[15];

					texcoord_buffer[_texcoord_amount + 10] = face_texcoord_buffer[12];
					texcoord_buffer[_texcoord_amount + 11] = face_texcoord_buffer[13];

					_texcoord_amount += 12;
					_vertices_amount += 18;
				}


				if (z == 15 || chunk[x + (z + 1) * 16 + y * 16 * 16] == BlockIndex::air)
				{
					vertex_buffer[_vertices_amount + 0] = bx_pos;
					vertex_buffer[_vertices_amount + 1] = y;
					vertex_buffer[_vertices_amount + 2] = bz_pos + 1;

					vertex_buffer[_vertices_amount + 3] = bx_pos + 1;
					vertex_buffer[_vertices_amount + 4] = y;
					vertex_buffer[_vertices_amount + 5] = bz_pos + 1;

					vertex_buffer[_vertices_amount + 6] = bx_pos + 1;
					vertex_buffer[_vertices_amount + 7] = y + 1;
					vertex_buffer[_vertices_amount + 8] = bz_pos + 1;

					vertex_buffer[_vertices_amount + 9] = bx_pos;
					vertex_buffer[_vertices_amount + 10] = y;
					vertex_buffer[_vertices_amount + 11] = bz_pos + 1;

					vertex_buffer[_vertices_amount + 12] = bx_pos;
					vertex_buffer[_vertices_amount + 13] = y + 1;
					vertex_buffer[_vertices_amount + 14] = bz_pos + 1;

					vertex_buffer[_vertices_amount + 15] = bx_pos + 1;
					vertex_buffer[_vertices_amount + 16] = y + 1;
					vertex_buffer[_vertices_amount + 17] = bz_pos + 1;


					texcoord_buffer[_texcoord_amount + 0] = face_texcoord_buffer[8];
					texcoord_buffer[_texcoord_amount + 1] = face_texcoord_buffer[9];

					texcoord_buffer[_texcoord_amount + 2] = face_texcoord_buffer[10];
					texcoord_buffer[_texcoord_amount + 3] = face_texcoord_buffer[11];

					texcoord_buffer[_texcoord_amount + 4] = face_texcoord_buffer[12];
					texcoord_buffer[_texcoord_amount + 5] = face_texcoord_buffer[13];

					texcoord_buffer[_texcoord_amount + 6] = face_texcoord_buffer[8];
					texcoord_buffer[_texcoord_amount + 7] = face_texcoord_buffer[9];

					texcoord_buffer[_texcoord_amount + 8] = face_texcoord_buffer[14];
					texcoord_buffer[_texcoord_amount + 9] = face_texcoord_buffer[15];

					texcoord_buffer[_texcoord_amount + 10] = face_texcoord_buffer[12];
					texcoord_buffer[_texcoord_amount + 11] = face_texcoord_buffer[13];

					_texcoord_amount += 12;
					_vertices_amount += 18;
				}

				if (x == 0 || chunk[(x - 1) + z * 16 + y * 16 * 16] == BlockIndex::air)
				{
					vertex_buffer[_vertices_amount + 0] = bx_pos;
					vertex_buffer[_vertices_amount + 1] = y;
					vertex_buffer[_vertices_amount + 2] = bz_pos;

					vertex_buffer[_vertices_amount + 3] = bx_pos;
					vertex_buffer[_vertices_amount + 4] = y;
					vertex_buffer[_vertices_amount + 5] = bz_pos + 1;

					vertex_buffer[_vertices_amount + 6] = bx_pos;
					vertex_buffer[_vertices_amount + 7] = y + 1;
					vertex_buffer[_vertices_amount + 8] = bz_pos + 1;

					vertex_buffer[_vertices_amount + 9] = bx_pos;
					vertex_buffer[_vertices_amount + 10] = y;
					vertex_buffer[_vertices_amount + 11] = bz_pos;

					vertex_buffer[_vertices_amount + 12] = bx_pos;
					vertex_buffer[_vertices_amount + 13] = y + 1;
					vertex_buffer[_vertices_amount + 14] = bz_pos;

					vertex_buffer[_vertices_amount + 15] = bx_pos;
					vertex_buffer[_vertices_amount + 16] = y + 1;
					vertex_buffer[_vertices_amount + 17] = bz_pos + 1;


					texcoord_buffer[_texcoord_amount + 0] = face_texcoord_buffer[8];
					texcoord_buffer[_texcoord_amount + 1] = face_texcoord_buffer[9];

					texcoord_buffer[_texcoord_amount + 2] = face_texcoord_buffer[10];
					texcoord_buffer[_texcoord_amount + 3] = face_texcoord_buffer[11];

					texcoord_buffer[_texcoord_amount + 4] = face_texcoord_buffer[12];
					texcoord_buffer[_texcoord_amount + 5] = face_texcoord_buffer[13];

					texcoord_buffer[_texcoord_amount + 6] = face_texcoord_buffer[8];
					texcoord_buffer[_texcoord_amount + 7] = face_texcoord_buffer[9];

					texcoord_buffer[_texcoord_amount + 8] = face_texcoord_buffer[14];
					texcoord_buffer[_texcoord_amount + 9] = face_texcoord_buffer[15];

					texcoord_buffer[_texcoord_amount + 10] = face_texcoord_buffer[12];
					texcoord_buffer[_texcoord_amount + 11] = face_texcoord_buffer[13];

					_texcoord_amount += 12;
					_vertices_amount += 18;
				}

				if (y == 0 || chunk[x + z * 16 + (y - 1) * 16 * 16] == BlockIndex::air)
				{
					vertex_buffer[_vertices_amount + 0] = bx_pos;
					vertex_buffer[_vertices_amount + 1] = y;
					vertex_buffer[_vertices_amount + 2] = bz_pos;

					vertex_buffer[_vertices_amount + 3] = bx_pos;
					vertex_buffer[_vertices_amount + 4] = y;
					vertex_buffer[_vertices_amount + 5] = bz_pos + 1;

					vertex_buffer[_vertices_amount + 6] = bx_pos + 1;
					vertex_buffer[_vertices_amount + 7] = y;
					vertex_buffer[_vertices_amount + 8] = bz_pos + 1;

					vertex_buffer[_vertices_amount + 9] = bx_pos;
					vertex_buffer[_vertices_amount + 10] = y;
					vertex_buffer[_vertices_amount + 11] = bz_pos;

					vertex_buffer[_vertices_amount + 12] = bx_pos + 1;
					vertex_buffer[_vertices_amount + 13] = y;
					vertex_buffer[_vertices_amount + 14] = bz_pos;

					vertex_buffer[_vertices_amount + 15] = bx_pos + 1;
					vertex_buffer[_vertices_amount + 16] = y;
					vertex_buffer[_vertices_amount + 17] = bz_pos + 1;

					texcoord_buffer[_texcoord_amount + 0] = face_texcoord_buffer[16];
					texcoord_buffer[_texcoord_amount + 1] = face_texcoord_buffer[17];

					texcoord_buffer[_texcoord_amount + 2] = face_texcoord_buffer[18];
					texcoord_buffer[_texcoord_amount + 3] = face_texcoord_buffer[19];

					texcoord_buffer[_texcoord_amount + 4] = face_texcoord_buffer[20];
					texcoord_buffer[_texcoord_amount + 5] = face_texcoord_buffer[21];

					texcoord_buffer[_texcoord_amount + 6] = face_texcoord_buffer[16];
					texcoord_buffer[_texcoord_amount + 7] = face_texcoord_buffer[17];

					texcoord_buffer[_texcoord_amount + 8] = face_texcoord_buffer[22];
					texcoord_buffer[_texcoord_amount + 9] = face_texcoord_buffer[23];

					texcoord_buffer[_texcoord_amount + 10] = face_texcoord_buffer[20];
					texcoord_buffer[_texcoord_amount + 11] = face_texcoord_buffer[21];

					_texcoord_amount += 12;
					_vertices_amount += 18;
				}


				if (y == 65 || chunk[x + z * 16 + (y + 1) * 16 * 16] == BlockIndex::air)
				{
					vertex_buffer[_vertices_amount + 0] = bx_pos;
					vertex_buffer[_vertices_amount + 1] = y + 1;
					vertex_buffer[_vertices_amount + 2] = bz_pos;

					vertex_buffer[_vertices_amount + 3] = bx_pos;
					vertex_buffer[_vertices_amount + 4] = y + 1;
					vertex_buffer[_vertices_amount + 5] = bz_pos + 1;

					vertex_buffer[_vertices_amount + 6] = bx_pos + 1;
					vertex_buffer[_vertices_amount + 7] = y + 1;
					vertex_buffer[_vertices_amount + 8] = bz_pos + 1;

					vertex_buffer[_vertices_amount + 9] = bx_pos;
					vertex_buffer[_vertices_amount + 10] = y + 1;
					vertex_buffer[_vertices_amount + 11] = bz_pos;

					vertex_buffer[_vertices_amount + 12] = bx_pos + 1;
					vertex_buffer[_vertices_amount + 13] = y + 1;
					vertex_buffer[_vertices_amount + 14] = bz_pos;

					vertex_buffer[_vertices_amount + 15] = bx_pos + 1;
					vertex_buffer[_vertices_amount + 16] = y + 1;
					vertex_buffer[_vertices_amount + 17] = bz_pos + 1;


					texcoord_buffer[_texcoord_amount + 0] = face_texcoord_buffer[0];
					texcoord_buffer[_texcoord_amount + 1] = face_texcoord_buffer[1];

					texcoord_buffer[_texcoord_amount + 2] = face_texcoord_buffer[2];
					texcoord_buffer[_texcoord_amount + 3] = face_texcoord_buffer[3];

					texcoord_buffer[_texcoord_amount + 4] = face_texcoord_buffer[4];
					texcoord_buffer[_texcoord_amount + 5] = face_texcoord_buffer[5];

					texcoord_buffer[_texcoord_amount + 6] = face_texcoord_buffer[0];
					texcoord_buffer[_texcoord_amount + 7] = face_texcoord_buffer[1];

					texcoord_buffer[_texcoord_amount + 8] = face_texcoord_buffer[6];
					texcoord_buffer[_texcoord_amount + 9] = face_texcoord_buffer[7];

					texcoord_buffer[_texcoord_amount + 10] = face_texcoord_buffer[4];
					texcoord_buffer[_texcoord_amount + 11] = face_texcoord_buffer[5];


					_texcoord_amount += 12;
					_vertices_amount += 18;
				}
			}
		}
	}

	glBindVertexArray(_vao);
	
	glBindBuffer(GL_ARRAY_BUFFER, _vertex_buffer);
	glBufferData(GL_ARRAY_BUFFER, _vertices_amount * sizeof(float), vertex_buffer, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, _texcoord_buffer);
	glBufferData(GL_ARRAY_BUFFER, _texcoord_amount * sizeof(float), texcoord_buffer, GL_STATIC_DRAW);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(1);

	glBindVertexArray(0);

	delete[] vertex_buffer;
	delete[] texcoord_buffer;
}

void ChunkRenderer::render()
{
	glBindVertexArray(_vao);

	glDrawArrays(GL_TRIANGLES, 0, _vertices_amount / 3);

	glBindVertexArray(0);
}