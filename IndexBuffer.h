#pragma once
#include <d3d11.h>
#pragma comment(lib, "d3d11.lib")
#include "Prerequisites.h"


class IndexBuffer
{
public:
	IndexBuffer(RenderSystem* system,void* list_indices,UINT size_list);

	UINT getSizeIndexList();

	~IndexBuffer();
private:
	UINT m_size_list;

	ID3D11Buffer* m_buffer;
	RenderSystem* m_system = nullptr;

	friend class DeviceContext;
};

