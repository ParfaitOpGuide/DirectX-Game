#include "Quads.h"
#include <iostream>


Quads::Quads()
{
	this->list[0] = { -0.1f, -0.1f, 0.0f, 1,0,0 };
	this->list[1] = { -0.1f, 0.1f, 0.0f,  0,1,0 };
	this->list[2] = { 0.1f, -0.1f, 0.0f,  0,0,0.5 };
	this->list[3] = { 0.1f, 0.1f, 0.0f,   1,1,0 };
}

Quads::Quads(float width, float height, float centerx, float centery, std::vector<vec3> colors)
{

	//note for future use, just take a vec of vec3s

		//bottom left
	list[0] = { centerx - width / 2, centery - height / 2, 0.0f,  colors[0] };
	//top left
	list[1] = { centerx - width / 2, centery + height / 2, 0.0f,  colors[1] };
	//bottom right
	list[2] = { centerx + width / 2, centery - height / 2, 0.0f,  colors[2] };
	//top right
	list[3] = { centerx + width / 2, centery + height / 2, 0.0f,   colors[3] };

}

void Quads::draw()
{
	//handles drawing
	GraphicsEngine::get()->getImmediateDeviceContext()->setVertexBuffer(m_vb);
	GraphicsEngine::get()->getImmediateDeviceContext()->drawTriangleStrip(m_vb->getSizeVertexList(), 0);
}

void Quads::createBuffer(void** shader_byte_code, size_t* size_shader)
{
	std::cout << "a";
	m_vb = GraphicsEngine::get()->createVertexBuffer();
	m_vb->load(list, sizeof(vertex), ARRAYSIZE(list), *shader_byte_code, *size_shader);
}

void Quads::destroy()
{
	m_vb->release();
}
