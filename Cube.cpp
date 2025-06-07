#include "Cube.h"
#include <iostream>
#include "IndexBuffer.h"
#include "VertexShader.h"
#include "PixelShader.h"
#include "EngineTime.h"


Cube::Cube() :AGameObject("default")
{
}

Cube::Cube(float width, float height, float depth, float centerx, float centery, float centerz, std::vector<Vector3D> colors, std::vector<Vector3D> colors2, string name) : AGameObject(name)
{


	this->setPosition(centerx, centery, centerz);
	this->setScale(width, height, depth);
	/*
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
	*/
	list[0] = { Vector3D(-.5f,-.5f,-.5f),  colors[0], colors2[0] };
	list[1] = { Vector3D(-.5f,.5f,-.5f),  colors[1], colors2[1] };
	list[2] = { Vector3D(.5f,.5f,-.5f),  colors[2], colors2[2] };
	list[3] = { Vector3D(.5f,-.5f,-.5f),  colors[3], colors2[3]};

	list[4] = { Vector3D(.5f,-.5f,.5f),  colors[0], colors2[0] };
	list[5] = { Vector3D(.5f,.5f,.5f),  colors[1], colors2[1] };
	list[6] = { Vector3D(-.5f,.5f,.5f),  colors[2], colors2[2] };
	list[7] = { Vector3D(-.5f,-.5f,.5f),  colors[3], colors2[3] };
	

	rotSpeed = 1.0f/(rand() % 700 + 300);
	//std::cout << rotSpeed << "\n";
	
}

void Cube::update(float deltaTime, float width, float height)
{
	constant cc;


	Matrix4x4 temp;

	//cc.m_world.setTranslation(Vector3D::lerp(Vector3D(-2, -2, 0), Vector3D(2, 2, 0), m_delta_pos));
	//cc.m_world.setScale(Vector3D::lerp(Vector3D(.5, .5, 0), Vector3D(2, 2, 0), (sin(m_delta_scale) + 1.f) / 2.f));

	//temp.setTranslation(Vector3D::lerp(Vector3D(-2, -2, 0), Vector3D(2, 2, 0), m_delta_pos));
	//cc.m_world *= temp;
	
	cc.m_world.setScale(Vector3D(this->getLocalScale().m_x, this->getLocalScale().m_y, this->getLocalScale().m_z));

	
	m_time += EngineTime::getDeltaTime();
	temp.setIdentity();
	temp.setRotationZ(m_time* rotSpeed);
	cc.m_world *= temp;

	temp.setIdentity();
	temp.setRotationY(m_time * rotSpeed);
	cc.m_world *= temp;

	temp.setIdentity();
	temp.setRotationX(m_time *rotSpeed);
	cc.m_world *= temp;
	
	temp.setIdentity();
	temp.setTranslation(Vector3D(this->getLocalPosition().m_x, this->getLocalPosition().m_y, this->getLocalPosition().m_z));
	cc.m_world *= temp;

	cc.m_view.setIdentity();
	cc.m_proj.setOrthoLH
	(
		width / 400.f,
		height / 400.f,
		-4.f,
		4.f
	);

	m_cb->update(GraphicsEngine::get()->getImmediateDeviceContext(), &cc);
}

void Cube::draw(float width, float height, VertexShader* m_vs, PixelShader* m_ps, float deltaTime)
{
	update(deltaTime, width, height);
	m_time += animation_speed * deltaTime;
	constant cc;
	cc.m_time = m_time;

	//handles drawing
	GraphicsEngine::get()->getImmediateDeviceContext()->setVertexBuffer(m_vb);
	GraphicsEngine::get()->getImmediateDeviceContext()->setIndexBuffer(m_ib);
	GraphicsEngine::get()->getImmediateDeviceContext()->setConstantBuffer(m_vs, m_cb);
	GraphicsEngine::get()->getImmediateDeviceContext()->setConstantBuffer(m_ps, m_cb);
	GraphicsEngine::get()->getImmediateDeviceContext()->drawIndexedTriangleList(m_ib->getSizeIndexList(), 0, 0);
}

void Cube::createBuffer(void** shader_byte_code, size_t* size_shader)
{
	//std::cout << "a";
	constant cc;
	cc.m_time = 0;

	m_cb = GraphicsEngine::get()->createConstantBuffer();
	m_cb->load(&cc, sizeof(constant));

	m_ib = GraphicsEngine::get()->createIndexBuffer();
	m_ib->load(index_list, ARRAYSIZE(index_list));

	m_vb = GraphicsEngine::get()->createVertexBuffer();
	m_vb->load(list, sizeof(vertex), ARRAYSIZE(list), *shader_byte_code, *size_shader);
}

void Cube::destroy()
{
	m_vb->release();
	m_ib->release();
	m_cb->release();
}