#pragma once
#include <d3d11.h>
#pragma comment(lib, "d3d11.lib")

class DeviceContext;

class ConstantBuffer
{
public:
	ConstantBuffer();

	bool load(void* buffer, UINT size_buffer);
	void update(DeviceContext* context, void* buffer);
	bool release();

private:
	ID3D11Buffer* m_buffer;


	friend class DeviceContext;
};

