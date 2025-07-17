#include "MeshObject.h"
#include <iostream>
#include "IndexBuffer.h"
#include "VertexShader.h"
#include "PixelShader.h"
#include "EngineTime.h"
#include "ViewportUIManager.h"


MeshObject::MeshObject() :AGameObject("default")
{
}

MeshObject::MeshObject(float width, float height, float depth, float centerx, float centery, float centerz, Vector3D speed, Vector3D rotation, std::vector<Vector3D> colors, std::vector<Vector3D> colors2, string name, RasterState* m_raster, MeshPtr mesh) : AGameObject(name)
{

	this->setRotation(rotation);
	this->setPosition(centerx, centery, centerz);
	this->setScale(width, height, depth);
	this->moveSpeed = speed;
	this->m_raster = m_raster;
	this->m_mesh = mesh;

	list[0] = { Vector3D(-.5f,-.5f,-.5f) };
	list[1] = { Vector3D(-.5f,.5f,-.5f) };
	list[2] = { Vector3D(.5f,.5f,-.5f) };
	list[3] = { Vector3D(.5f,-.5f,-.5f) };

	list[4] = { Vector3D(.5f,-.5f,.5f) };
	list[5] = { Vector3D(.5f,.5f,.5f) };
	list[6] = { Vector3D(-.5f,.5f,.5f) };
	list[7] = { Vector3D(-.5f,-.5f,.5f) };

	texlist[0] = { Vector2D(0.0f,0.0f) };
	texlist[1] = { Vector2D(0.0f,1.0f) };
	texlist[2] = { Vector2D(1.0f,0.0f) };
	texlist[3] = { Vector2D(1.0f,1.0f) };

	finlist[0] = { list[0], texlist[1] };
	finlist[1] = { list[1], texlist[0] };
	finlist[2] = { list[2], texlist[2] };
	finlist[3] = { list[3], texlist[3] };

	finlist[4] = { list[4], texlist[1] };
	finlist[5] = { list[5], texlist[0] };
	finlist[6] = { list[6], texlist[2] };
	finlist[7] = { list[7], texlist[3] };

	finlist[8] = { list[1], texlist[1] };
	finlist[9] = { list[6], texlist[0] };
	finlist[10] = { list[5], texlist[2] };
	finlist[11] = { list[2], texlist[3] };

	finlist[12] = { list[7], texlist[1] };
	finlist[13] = { list[0], texlist[0] };
	finlist[14] = { list[3], texlist[2] };
	finlist[15] = { list[4], texlist[3] };

	finlist[16] = { list[3], texlist[1] };
	finlist[17] = { list[2], texlist[0] };
	finlist[18] = { list[5], texlist[2] };
	finlist[19] = { list[4], texlist[3] };

	finlist[20] = { list[7], texlist[1] };
	finlist[21] = { list[6], texlist[0] };
	finlist[22] = { list[1], texlist[2] };
	finlist[23] = { list[0], texlist[3] };

	rotSpeed = 1.0f / (rand() % 700 + 300);
	//std::cout << rotSpeed << "\n";

}

void MeshObject::update(float deltaTime, float width, float height, Camera cam, bool isPers)
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

void MeshObject::draw(float width, float height, VertexShaderPtr m_vs, PixelShaderPtr m_ps, float deltaTime, std::vector<Camera> camList, int currentCam)
{
	ticked = false;
	m_raster->toggleWireframe(ViewportUIManager::getInstance()->getWireframeCameraBool(1));
	update(deltaTime, width, height, camList[ViewportUIManager::getInstance()->getViewCameraNum(1)], ViewportUIManager::getInstance()->getPerspectiveCameraBool(1));
	ticked = true;

	//handles drawing
	GraphicsEngine::get()->getRenderSystem()->getImmediateDeviceContext()->setVertexBuffer(m_mesh->getVertexBuffer());
	GraphicsEngine::get()->getRenderSystem()->getImmediateDeviceContext()->setIndexBuffer(m_mesh->getIndexBuffer());
	GraphicsEngine::get()->getRenderSystem()->getImmediateDeviceContext()->setConstantBuffer(m_vs, m_cb);
	GraphicsEngine::get()->getRenderSystem()->getImmediateDeviceContext()->setConstantBuffer(m_ps, m_cb);
	GraphicsEngine::get()->getRenderSystem()->getImmediateDeviceContext()->drawIndexedTriangleList(m_mesh->getIndexBuffer()->getSizeIndexList(), 0, 0, 0);
	m_raster->toggleWireframe(ViewportUIManager::getInstance()->getWireframeCameraBool(2));
	update(deltaTime, width, height, camList[ViewportUIManager::getInstance()->getViewCameraNum(2)], ViewportUIManager::getInstance()->getPerspectiveCameraBool(2));
	GraphicsEngine::get()->getRenderSystem()->getImmediateDeviceContext()->drawIndexedTriangleList(m_mesh->getIndexBuffer()->getSizeIndexList(), 0, 0, 1);
	m_raster->toggleWireframe(ViewportUIManager::getInstance()->getWireframeCameraBool(3));
	update(deltaTime, width, height, camList[ViewportUIManager::getInstance()->getViewCameraNum(3)], ViewportUIManager::getInstance()->getPerspectiveCameraBool(3));
	GraphicsEngine::get()->getRenderSystem()->getImmediateDeviceContext()->drawIndexedTriangleList(m_mesh->getIndexBuffer()->getSizeIndexList(), 0, 0, 2);

	m_time += animation_speed * deltaTime;
	constant cc;
	cc.m_time = m_time;
}

void MeshObject::createBuffer(void** shader_byte_code, size_t* size_shader)
{
	//std::cout << "a";
	constant cc;
	cc.m_time = 0;

	m_cb = GraphicsEngine::get()->getRenderSystem()->createConstantBuffer(&cc, sizeof(constant));

	m_ib = GraphicsEngine::get()->getRenderSystem()->createIndexBuffer(index_list, ARRAYSIZE(index_list));

	m_vb = GraphicsEngine::get()->getRenderSystem()->createVertexBuffer(finlist, sizeof(vertex), ARRAYSIZE(finlist), *shader_byte_code, *size_shader);
}

void MeshObject::createBuffer(MeshObject copy)
{
	//std::cout << "a";
	constant cc;
	cc.m_time = 0;

	m_cb = copy.m_cb;

	m_ib = copy.m_ib;

	m_vb = copy.m_vb;
}

void MeshObject::destroy()
{
}