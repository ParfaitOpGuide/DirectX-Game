#include "Cube.h"
#include <iostream>
#include "IndexBuffer.h"
#include "VertexShader.h"
#include "PixelShader.h"
#include "EngineTime.h"
#include "ViewportUIManager.h"


Cube::Cube() :AGameObject("default")
{
}

Cube::Cube(float width, float height, float depth, float centerx, float centery, float centerz, Vector3D speed, Vector3D rotation, std::vector<Vector3D> colors, std::vector<Vector3D> colors2, string name, RasterState* m_raster) : AGameObject(name)
{

	this->setRotation(rotation);
	this->setPosition(centerx, centery, centerz);
	this->setScale(width, height, depth);
	this->moveSpeed = speed;
	this->m_raster = m_raster;
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
	list[3] = { Vector3D(.5f,-.5f,-.5f),  colors[3], colors2[3] };

	list[4] = { Vector3D(.5f,-.5f,.5f),  colors[0], colors2[0] };
	list[5] = { Vector3D(.5f,.5f,.5f),  colors[1], colors2[1] };
	list[6] = { Vector3D(-.5f,.5f,.5f),  colors[2], colors2[2] };
	list[7] = { Vector3D(-.5f,-.5f,.5f),  colors[3], colors2[3] };


	rotSpeed = 1.0f / (rand() % 700 + 300);
	//std::cout << rotSpeed << "\n";

}

void Cube::update(float deltaTime, float width, float height, Camera cam, bool isPers)
{
	constant cc;


	Matrix4x4 temp;

	cc.m_world.setScale(Vector3D(this->getLocalScale().m_x, this->getLocalScale().m_y, this->getLocalScale().m_z));
	//cc.m_world.setScale(Vector3D::lerp(Vector3D(1.6, .001, 1.6), Vector3D(.5, .5, .5), (sin(m_time * 0.0007f) + 1.f) / 2.f));

	m_time += EngineTime::getDeltaTime();
	temp.setIdentity();
	//temp.setRotationZ(m_time * rotSpeed);
	temp.setRotationZ(this->getLocalRotation().m_z);
	cc.m_world *= temp;

	temp.setIdentity();
	temp.setRotationY(this->getLocalRotation().m_y);
	cc.m_world *= temp;

	temp.setIdentity();
	temp.setRotationX(this->getLocalRotation().m_x);
	cc.m_world *= temp;
	if (!ticked) {
		if (std::abs(this->getLocalPosition().m_x) + (this->getLocalScale().m_x / 2.0) >= 1.25f)
			moveSpeed.m_x = -moveSpeed.m_x;
		if (std::abs(this->getLocalPosition().m_y) + (this->getLocalScale().m_y / 2.0) >= 0.9f)
			moveSpeed.m_y = -moveSpeed.m_y;
	}
	//no check for z because no bounding box
	Vector3D pos = this->getLocalPosition();
	pos.m_x += moveSpeed.m_x;
	pos.m_y += moveSpeed.m_y;
	pos.m_z += moveSpeed.m_z;



	this->setPosition(pos);


	temp.setIdentity();
	temp.setTranslation(Vector3D(this->getLocalPosition().m_x, this->getLocalPosition().m_y, this->getLocalPosition().m_z));
	//temp.setTranslation(Vector3D::lerp(Vector3D(-1, -.6, 0), Vector3D(1, .6, 0), (sin(m_time * 0.001f) + 1.f) / 2.f));
	cc.m_world *= temp;
	if (!isPers) {
		cc.m_view.setIdentity();
		cc.m_proj.setOrthoLH
		(
			width / 400.f,
			height / 400.f,
			-2.f,
			2.f
		);

	}
	else
	{
		cc.m_view = cam.GetViewMatrix4();
		cc.m_proj = cam.GetProjectionMatrix4();
	}

	m_cb->update(GraphicsEngine::get()->getRenderSystem()->getImmediateDeviceContext(), &cc);
}

void Cube::draw(float width, float height, VertexShader* m_vs, PixelShader* m_ps, float deltaTime, std::vector<Camera> camList, int currentCam)
{
	ticked = false;
	m_raster->toggleWireframe(ViewportUIManager::getInstance()->getWireframeCameraBool(1));
	update(deltaTime, width, height, camList[ViewportUIManager::getInstance()->getViewCameraNum(1)], ViewportUIManager::getInstance()->getPerspectiveCameraBool(1));
	ticked = true;


	//handles drawing
	GraphicsEngine::get()->getRenderSystem()->getImmediateDeviceContext()->setVertexBuffer(m_vb);
	GraphicsEngine::get()->getRenderSystem()->getImmediateDeviceContext()->setIndexBuffer(m_ib);
	GraphicsEngine::get()->getRenderSystem()->getImmediateDeviceContext()->setConstantBuffer(m_vs, m_cb);
	GraphicsEngine::get()->getRenderSystem()->getImmediateDeviceContext()->setConstantBuffer(m_ps, m_cb);
	GraphicsEngine::get()->getRenderSystem()->getImmediateDeviceContext()->drawIndexedTriangleList(m_ib->getSizeIndexList(), 0, 0, 0);
	m_raster->toggleWireframe(ViewportUIManager::getInstance()->getWireframeCameraBool(2));
	update(deltaTime, width, height, camList[ViewportUIManager::getInstance()->getViewCameraNum(2)], ViewportUIManager::getInstance()->getPerspectiveCameraBool(2));
	GraphicsEngine::get()->getRenderSystem()->getImmediateDeviceContext()->drawIndexedTriangleList(m_ib->getSizeIndexList(), 0, 0, 1);
	m_raster->toggleWireframe(ViewportUIManager::getInstance()->getWireframeCameraBool(3));
	update(deltaTime, width, height, camList[ViewportUIManager::getInstance()->getViewCameraNum(3)], ViewportUIManager::getInstance()->getPerspectiveCameraBool(3));
	GraphicsEngine::get()->getRenderSystem()->getImmediateDeviceContext()->drawIndexedTriangleList(m_ib->getSizeIndexList(), 0, 0, 2);

	m_time += animation_speed * deltaTime;
	constant cc;
	cc.m_time = m_time;
}

void Cube::createBuffer(void** shader_byte_code, size_t* size_shader)
{
	//std::cout << "a";
	constant cc;
	cc.m_time = 0;

	m_cb = GraphicsEngine::get()->getRenderSystem()->createConstantBuffer(&cc, sizeof(constant));

	m_ib = GraphicsEngine::get()->getRenderSystem()->createIndexBuffer(index_list, ARRAYSIZE(index_list));

	m_vb = GraphicsEngine::get()->getRenderSystem()->createVertexBuffer(list, sizeof(vertex), ARRAYSIZE(list), *shader_byte_code, *size_shader);
}

void Cube::createBuffer(Cube copy)
{
	//std::cout << "a";
	constant cc;
	cc.m_time = 0;

	m_cb = copy.m_cb;

	m_ib = copy.m_ib;

	m_vb = copy.m_vb;
}

void Cube::destroy()
{
}