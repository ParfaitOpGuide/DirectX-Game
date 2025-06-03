#include "Cube.h"
#include <iostream>
#include <filesystem>
#include "IndexBuffer.h"
#include <WICTextureLoader.h>
Cube::Cube()
{

	list[0] = { Vector3D(-0.5f, +0.5f, 0.0f), Vector2D(0.0f, 1.0f) }; // Top left vertex
	list[1] = { Vector3D(+0.5f, +0.5f, 0.0f), Vector2D(1.0f, 1.0f) }; // Top right vertex
	list[2] = { Vector3D(+0.5f, -0.5f, 0.0f), Vector2D(1.0f, 0.0f) }; // Bottom Right vertex
	list[3] = { Vector3D(-0.5f, -0.5f, 0.0f), Vector2D(0.0f, 0.0f) }; // Bottom left vertex
}

Cube::Cube(float width, float height, float depth, float centerx, float centery, float centerz, std::vector<Vector3D> colors, std::vector<Vector3D> colors2)
{

	//note for future use, just take a vec of vec3s

	//back bottom left
	poslist[0] = { Vector3D(centerx - width / 2, centery - height / 2, centerz - depth / 2) };
	//back top left
	poslist[1] = { Vector3D(centerx - width / 2, centery + height / 2, centerz - depth / 2) };
	//back top right 
	poslist[2] = { Vector3D(centerx + width / 2, centery + height / 2, centerz - depth / 2) };
	//back bottom right
	poslist[3] = { Vector3D(centerx + width / 2, centery - height / 2, centerz - depth / 2) };
	//front bottom right
	poslist[4] = { Vector3D(centerx + width / 2, centery - height / 2, centerz + depth / 2) };
	//front top right
	poslist[5] = { Vector3D(centerx + width / 2, centery + height / 2, centerz + depth / 2) };
	//front top left
	poslist[6] = { Vector3D(centerx - width / 2, centery + height / 2, centerz + depth / 2) };
	//front bottom left
	poslist[7] = { Vector3D(centerx - width / 2, centery - height / 2, centerz + depth / 2) };

	coordlist[0] = Vector2D(0.0f, 0.0f);
	coordlist[1] = Vector2D(0.0f, 1.0f);
	coordlist[2] = Vector2D(1.0f, 0.0f);
	coordlist[3] = Vector2D(1.0f, 1.0f);

	list[0] = { poslist[0],coordlist[1] };
	list[1] = { poslist[1],coordlist[0] };
	list[2] = { poslist[2],coordlist[2] };
	list[3] = { poslist[3],coordlist[3] };
	/*
		list[4] = { poslist[4],coordlist[1] };
		list[5] = { poslist[5],coordlist[0] };
		list[6] = { poslist[6],coordlist[2] };
		list[7] = { poslist[7],coordlist[3] };

		list[8] = { poslist[1],coordlist[1] };
		list[9] = { poslist[6],coordlist[0] };
		list[10] = { poslist[5],coordlist[2] };
		list[11] = { poslist[2],coordlist[3] };

		list[12] = { poslist[7],coordlist[1] };
		list[13] = { poslist[0],coordlist[0] };
		list[14] = { poslist[3],coordlist[2] };
		list[15] = { poslist[4],coordlist[3] };

		list[16] = { poslist[3],coordlist[1] };
		list[17] = { poslist[2],coordlist[0] };
		list[18] = { poslist[5],coordlist[2] };
		list[19] = { poslist[4],coordlist[3] };

		list[20] = { poslist[7],coordlist[1] };
		list[21] = { poslist[6],coordlist[0] };
		list[22] = { poslist[1],coordlist[2] };
		list[23] = { poslist[0],coordlist[3] };
		*/
	LoadTexture();
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

void Cube::LoadTexture()
{
	std::wstring path = L"Wood_Crate_001_basecolor.jpg";
	bool filepathExists = std::filesystem::is_directory(path);
	if (!filepathExists) {
		{
			std::cout << "Could not load file";
			return;
		}
	}
	// Load texture into a resource shader view
	ID3D11Device* device = GraphicsEngine::get()->getDevice();
	ID3D11DeviceContext* context = GraphicsEngine::get()->getDeviceContext();

	ComPtr<ID3D11Resource> resource = nullptr;
	DirectX::CreateWICTextureFromFile(device, context, path.c_str(), resource.ReleaseAndGetAddressOf(), m_DiffuseTexture.ReleaseAndGetAddressOf());
	if (resource == nullptr) {
		{
			std::cout << "broken";
			return;
		}
	}
}
