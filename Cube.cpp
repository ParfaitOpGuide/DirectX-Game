#include "Cube.h"
#include <iostream>
#include "IndexBuffer.h"


Cube::Cube()
{
}

Cube::Cube(float width, float height, float depth, float centerx, float centery, float centerz, std::vector<Vector3D> colors, std::vector<Vector3D> colors2)
{

	//note for future use, just take a vec of vec3s

	//back bottom left
	list[0] = { Vector3D(centerx - width / 2, centery - height / 2, centerz - depth / 2),  colors[0], colors2[0] };
	//back top left
	list[1] = { Vector3D(centerx - width / 2, centery + height / 2, centerz - depth / 2),  colors[1], colors2[1] };
	//back top right 
	list[2] = { Vector3D(centerx + width / 2, centery + height / 2, centerz - depth / 2),  colors[2], colors2[2] };
	//back bottom right
	list[3] = { Vector3D(centerx + width / 2, centery - height / 2, centerz - depth / 2),  colors[3], colors2[3] };
	//front bottom right
	list[4] = { Vector3D(centerx + width / 2, centery - height / 2, centerz + depth / 2),  colors[0], colors2[0] };
	//front top right
	list[5] = { Vector3D(centerx + width / 2, centery + height / 2, centerz + depth / 2),  colors[1], colors2[1] };
	//front top left
	list[6] = { Vector3D(centerx - width / 2, centery + height / 2, centerz + depth / 2),  colors[2], colors2[2] };
	//front bottom left
	list[7] = { Vector3D(centerx - width / 2, centery - height / 2, centerz + depth / 2),  colors[3], colors2[3] };

}

void Cube::draw()
{
	//handles drawing
	GraphicsEngine::get()->getImmediateDeviceContext()->setVertexBuffer(m_vb);
	GraphicsEngine::get()->getImmediateDeviceContext()->setIndexBuffer(m_ib);
	GraphicsEngine::get()->getImmediateDeviceContext()->drawIndexedTriangleList(m_ib->getSizeIndexList(), 0, 0);
}

void Cube::createBuffer(void** shader_byte_code, size_t* size_shader)
{
	std::cout << "a";

	
	

	m_ib = GraphicsEngine::get()->createIndexBuffer();
	m_ib->load(index_list, ARRAYSIZE(index_list));

	m_vb = GraphicsEngine::get()->createVertexBuffer();
	m_vb->load(list, sizeof(vertex), ARRAYSIZE(list), *shader_byte_code, *size_shader);
}

void Cube::destroy()
{
	m_vb->release();
	m_ib->release();
}