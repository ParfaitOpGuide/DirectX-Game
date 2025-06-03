#pragma once
#include <vector>
#include "VertexBuffer.h"
#include "GraphicsEngine.h"
#include "DeviceContext.h"
#include "Vector3D.h"
#include "Vector2D.h"
#include "Matrix4x4.h"
#include <wrl.h>
#include <d3d11.h>
#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "d3dcompiler.lib")
using namespace Microsoft::WRL;

struct vertex
{
	Vector3D position;
	Vector2D texcoord;
};

class Cube
{
public:
	Cube();
	//constructor that makes it so we only need to give our center and size for recs and squares
	//different class needed for triangles in the future
	Cube(float width, float height, float depth, float centerx, float centery, float centerz, std::vector<Vector3D> colors, std::vector<Vector3D> colors2);

	void draw();
	void createBuffer(void** shader_byte_code, size_t* size_shader);
	void destroy();

	vertex list[4];
	Vector2D coordlist[4];
	Vector3D poslist[8];
	VertexBuffer* m_vb;
	IndexBuffer* m_ib;
	int index_list[36] =
	{
		//front
		0,1,2, // first tri
		2,3,0, // second tri
		//back
		4,5,6, // third tri
		6,7,4, //fourth tri
		//top
		8,9,10,
		10,11,8,
		//bottom
		12,13,14,
		14,15,12,
		//right
		16,17,18,
		18,19,16,
		//left
		20,21,22,
		22,23,20
	};

	void LoadTexture();
	ComPtr<ID3D11ShaderResourceView> m_DiffuseTexture = nullptr;
};
