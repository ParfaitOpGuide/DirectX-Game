#pragma once
#include <vector>
#include "VertexBuffer.h"
#include "GraphicsEngine.h"
#include "DeviceContext.h"

struct vec3
{
	float x, y, z;
};

struct vertex
{
	vec3 position;
	vec3 color;
};

class Quads
{
public:
	Quads();
	//constructor that makes it so we only need to give our center and size for recs and squares
	//different class needed for triangles in the future
	Quads(float width, float height, float centerx, float centery, std::vector<vec3> colors);

	void draw();
	void createBuffer(void** shader_byte_code, size_t* size_shader);
	void destroy();

	vertex list[4];
	VertexBuffer* m_vb;
};

