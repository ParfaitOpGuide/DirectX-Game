#include "Quads.h"
#include <iostream>


Quads::Quads()
{
}

Quads::Quads(float width, float height, float centerx, float centery, std::vector<Vector3D> colors, std::vector<Vector3D> colors2)
{

	//note for future use, just take a vec of vec3s

		//bottom left
	list[0] = { Vector3D(centerx - width / 2, centery - height / 2, 0.0f)};
	//top left
	list[1] = { Vector3D(centerx - width / 2, centery + height / 2, 0.0f)};
	//bottom right
	list[2] = { Vector3D(centerx + width / 2, centery - height / 2, 0.0f)};
	//top right
	list[3] = { Vector3D(centerx + width / 2, centery + height / 2, 0.0f)};

}

void Quads::draw()
{
	//handles drawing
	GraphicsEngine::get()->getImmediateDeviceContext()->setVertexBuffer(m_vb);
	GraphicsEngine::get()->getImmediateDeviceContext()->drawTriangleStrip(m_vb->getSizeVertexList(), 0);
}

void Quads::createBuffer(void** shader_byte_code, size_t* size_shader)
{
//	std::cout << "a";
	m_vb = GraphicsEngine::get()->createVertexBuffer();
	m_vb->load(list, sizeof(vertex), ARRAYSIZE(list), *shader_byte_code, *size_shader);
}

void Quads::destroy()
{
	m_vb->release();
}