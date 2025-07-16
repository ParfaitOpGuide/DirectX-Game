#include "Quads.h"
#include "EngineTime.h"
#include "ViewportUIManager.h"
#include <iostream>


Quads::Quads() :AGameObject("default")
{
}

Quads::Quads(float width, float height, float depth, float centerx, float centery, float centerz, std::vector<Vector3D> colors, std::vector<Vector3D> colors2, string name) : AGameObject(name)
{


	this->setPosition(centerx, centery, centerz);
	this->setScale(width, height, depth);

	list[0] = { Vector3D(-.5f,-.5f,0.f),  colors[0], colors2[0] };
	list[1] = { Vector3D(-.5f,.5f,0.f),  colors[1], colors2[1] };
	list[2] = { Vector3D(.5f,.5f,0.f),  colors[2], colors2[2] };
	list[3] = { Vector3D(.5f,-.5f,0.f),  colors[3], colors2[3] };


	rotSpeed = 0;
	//std::cout << rotSpeed << "\n";

}

void Quads::update(float deltaTime, float width, float height, Camera cam, bool isPers)
{
	constant cc;


	Matrix4x4 temp;

	//cc.m_world.setTranslation(Vector3D::lerp(Vector3D(-2, -2, 0), Vector3D(2, 2, 0), m_delta_pos));
	//cc.m_world.setScale(Vector3D::lerp(Vector3D(.5, .5, 0), Vector3D(2, 2, 0), (sin(m_delta_scale) + 1.f) / 2.f));

	//temp.setTranslation(Vector3D::lerp(Vector3D(-2, -2, 0), Vector3D(2, 2, 0), m_delta_pos));
	//cc.m_world *= temp;

	cc.m_world.setScale(Vector3D(this->getLocalScale().m_x, this->getLocalScale().m_y, this->getLocalScale().m_z));

	//important note, rotation is in radians so take this copy paste for 90 degrees 1.5708
	m_time += EngineTime::getDeltaTime();
	temp.setIdentity();
	temp.setRotationZ(0);
	cc.m_world *= temp;

	temp.setIdentity();
	temp.setRotationY(0);
	cc.m_world *= temp;

	temp.setIdentity();
	temp.setRotationX(1.5708);
	cc.m_world *= temp;

	temp.setIdentity();
	temp.setTranslation(Vector3D(this->getLocalPosition().m_x, this->getLocalPosition().m_y, this->getLocalPosition().m_z));
	cc.m_world *= temp;
	/*
	cc.m_view.setIdentity();
	cc.m_proj.setOrthoLH
	(
		width / 400.f,
		height / 400.f,
		-4.f,
		4.f
	);*/

	cc.m_view = cam.GetViewMatrix4();
	cc.m_proj = cam.GetProjectionMatrix4();

	m_cb->update(GraphicsEngine::get()->getImmediateDeviceContext(), &cc);
}

void Quads::draw(float width, float height, VertexShader* m_vs, PixelShader* m_ps, float deltaTime, std::vector<Camera> camList, int currentCam)
{
	ticked = false;
	m_raster->toggleWireframe(ViewportUIManager::getInstance()->getWireframeCameraBool(1));
	update(deltaTime, width, height, camList[ViewportUIManager::getInstance()->getViewCameraNum(1)], ViewportUIManager::getInstance()->getPerspectiveCameraBool(1));
	ticked = true;


	//handles drawing
	GraphicsEngine::get()->getImmediateDeviceContext()->setVertexBuffer(m_vb);
	GraphicsEngine::get()->getImmediateDeviceContext()->setIndexBuffer(m_ib);
	GraphicsEngine::get()->getImmediateDeviceContext()->setConstantBuffer(m_vs, m_cb);
	GraphicsEngine::get()->getImmediateDeviceContext()->setConstantBuffer(m_ps, m_cb);
	GraphicsEngine::get()->getImmediateDeviceContext()->drawIndexedTriangleList(m_ib->getSizeIndexList(), 0, 0, 0);
	m_raster->toggleWireframe(ViewportUIManager::getInstance()->getWireframeCameraBool(2));
	update(deltaTime, width, height, camList[ViewportUIManager::getInstance()->getViewCameraNum(2)], ViewportUIManager::getInstance()->getPerspectiveCameraBool(2));
	GraphicsEngine::get()->getImmediateDeviceContext()->drawIndexedTriangleList(m_ib->getSizeIndexList(), 0, 0, 1);
	m_raster->toggleWireframe(ViewportUIManager::getInstance()->getWireframeCameraBool(3));
	update(deltaTime, width, height, camList[ViewportUIManager::getInstance()->getViewCameraNum(3)], ViewportUIManager::getInstance()->getPerspectiveCameraBool(3));
	GraphicsEngine::get()->getImmediateDeviceContext()->drawIndexedTriangleList(m_ib->getSizeIndexList(), 0, 0, 2);

	m_time += animation_speed * deltaTime;
	constant cc;
	cc.m_time = m_time;
}

void Quads::createBuffer(void** shader_byte_code, size_t* size_shader)
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

void Quads::createBuffer(Quads copy)
{
	//std::cout << "a";
	constant cc;
	cc.m_time = 0;

	m_cb = copy.m_cb;

	m_ib = copy.m_ib;

	m_vb = copy.m_vb;
}

void Quads::destroy()
{
	m_vb->release();
	m_ib->release();
	m_cb->release();
}