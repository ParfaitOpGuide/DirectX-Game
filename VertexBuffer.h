#pragma once
#include <d3d11.h>
#pragma comment(lib, "d3d11.lib")

class DeviceContext;

class VertexBuffer
{
public:
	VertexBuffer();

	bool load(void* list_vertices, UINT size_vertex, UINT size_list, void* shader_byte_code, UINT size_byte_shader);
	UINT getSizeVertexList();
	bool release();

private:
	UINT m_size_vertex;
	UINT m_size_list;

	ID3D11Buffer* m_buffer;
	ID3D11InputLayout* m_layout; 

	friend class DeviceContext;
};

