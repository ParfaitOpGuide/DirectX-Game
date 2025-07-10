#include "Circle.h"
#include <iostream>
#include "IndexBuffer.h"
#include "VertexShader.h"
#include "PixelShader.h"
#include "EngineTime.h"
#include "CameraNumHolder.h"



Circle::Circle() :AGameObject("default")
{
}

Circle::Circle(float width, float height, float depth, float centerx, float centery, float centerz, Vector3D speed, std::vector<Vector3D> colors, std::vector<Vector3D> colors2, string name) : AGameObject(name)
{


	this->setPosition(centerx, centery, centerz);
	this->setScale(width, height, depth);
	this->moveSpeed = speed;

	for (int i = 0; i < 40; i++) {
		this->list[i] = { Vector3D(std::cos(i / 39.0f * (2.0*3.1415f)) * .5f,std::sin(i / 39.0f * (2.0 * 3.1415f)) * .5f,.0f),  colors[0], colors2[0] };
	}


	rotSpeed = 1.0f / (rand() % 700 + 300);
	//std::cout << rotSpeed << "\n";

}

void Circle::update(float deltaTime, float width, float height, Camera cam)
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
	//temp.setRotationZ(m_time* rotSpeed);
	temp.setRotationZ(0);
	cc.m_world *= temp;

	temp.setIdentity();
	temp.setRotationY(0);
	cc.m_world *= temp;

	temp.setIdentity();
	temp.setRotationX(0);
	cc.m_world *= temp;

	if (std::abs(this->getLocalPosition().m_x) + (this->getLocalScale().m_x / 2.0) >= 1.25f)
		moveSpeed.m_x = -moveSpeed.m_x;
	if (std::abs(this->getLocalPosition().m_y) + (this->getLocalScale().m_y / 2.0) >= 0.9f)
		moveSpeed.m_y = -moveSpeed.m_y;
	//no check for z because no bounding box
	Vector3D pos = this->getLocalPosition();
	pos.m_x += moveSpeed.m_x;
	pos.m_y += moveSpeed.m_y;
	pos.m_z += moveSpeed.m_z;



	this->setPosition(pos);

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

	//cc.m_view = cam.GetViewMatrix4();
	//cc.m_proj = cam.GetProjectionMatrix4();

	m_cb->update(GraphicsEngine::get()->getImmediateDeviceContext(), &cc);
}

void Circle::draw(float width, float height, VertexShader* m_vs, PixelShader* m_ps, float deltaTime, std::vector<Camera> camList, int currentCam)
{
	ticked = false;
	update(deltaTime, width, height, camList[0]);
	ticked = true;


	//handles drawing
	GraphicsEngine::get()->getImmediateDeviceContext()->setVertexBuffer(m_vb);
	GraphicsEngine::get()->getImmediateDeviceContext()->setIndexBuffer(m_ib);
	GraphicsEngine::get()->getImmediateDeviceContext()->setConstantBuffer(m_vs, m_cb);
	GraphicsEngine::get()->getImmediateDeviceContext()->setConstantBuffer(m_ps, m_cb);
	GraphicsEngine::get()->getImmediateDeviceContext()->drawIndexedTriangleList(m_ib->getSizeIndexList(), 0, 0, 0);
	update(deltaTime, width, height, camList[4]);
	GraphicsEngine::get()->getImmediateDeviceContext()->drawIndexedTriangleList(m_ib->getSizeIndexList(), 0, 0, 1);
	update(deltaTime, width, height, camList[currentCam]);
	GraphicsEngine::get()->getImmediateDeviceContext()->drawIndexedTriangleList(m_ib->getSizeIndexList(), 0, 0, 2);

	m_time += animation_speed * deltaTime;
	constant cc;
	cc.m_time = m_time;
}

void Circle::createBuffer(void** shader_byte_code, size_t* size_shader)
{
	unsigned int index_list[] =
	{
		0,1,2,
		0,2,3,
		0,3,4,
		0,4,5,
		0,5,6,
		0,6,7,
		0,7,8,
		0,8,9,
		0,9,10,
		0,10,11,
		0,11,12,
		0,12,13,
		0,13,14,
		0,14,15,
		0,15,16,
		0,16,17,
		0,17,18,
		0,18,19,
		0,19,20,
		0,20,21,
		0,21,22,
		0,22,23,
		0,23,24,
		0,24,25,
		0,25,26,
		0,26,27,
		0,27,28,
		0,28,29,
		0,29,30,
		0,30,31,
		0,31,32,
		0,32,33,
		0,33,34,
		0,34,35,
		0,35,36,
		0,36,37,
		0,37,38,
		0,38,39,
		0,39,1,
	};

	constant cc;
	cc.m_time = 0;

	m_cb = GraphicsEngine::get()->createConstantBuffer();
	m_cb->load(&cc, sizeof(constant));

	m_ib = GraphicsEngine::get()->createIndexBuffer();
	m_ib->load(index_list, ARRAYSIZE(index_list));

	m_vb = GraphicsEngine::get()->createVertexBuffer();
	m_vb->load(list, sizeof(vertex), ARRAYSIZE(list), *shader_byte_code, *size_shader);
}

void Circle::createBuffer(Circle copy)
{
	//std::cout << "a";
	constant cc;
	cc.m_time = 0;

	m_cb = copy.m_cb;

	m_ib = copy.m_ib;

	m_vb = copy.m_vb;
}

void Circle::destroy()
{
	m_vb->release();
	m_ib->release();
	m_cb->release();
}