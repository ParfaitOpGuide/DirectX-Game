#pragma once
#include <vector>
#include "VertexBuffer.h"
#include "ConstantBuffer.h"
#include "GraphicsEngine.h"
#include "AGameObject.h"
#include "DeviceContext.h"
#include "Vector3D.h"
#include "Matrix4x4.h"
#include "Camera.h"



class Circle : public AGameObject
{
public:
	Circle();
	Circle(float width, float height, float depth, float centerx, float centery, float centerz, Vector3D speed, std::vector<Vector3D> colors, std::vector<Vector3D> colors2, string name);

	void update(float deltaTime, float width, float height, Camera cam);
	void draw(float width, float height, VertexShader* m_vs, PixelShader* m_ps, float deltaTime, std::vector<Camera> camList, int currentCam);;
	void createBuffer(void** shader_byte_code, size_t* size_shader);
	void createBuffer(Circle copy);
	void destroy();

	vertex list[40];
	VertexBuffer* m_vb;
	IndexBuffer* m_ib;
	ConstantBuffer* m_cb;
	
	float m_time = 0;
	float animation_speed = 1000.0f;
	float change_speed = 5.0f;
	bool increasing;
	float rotSpeed;
	Vector3D moveSpeed;
	bool ticked;
};
