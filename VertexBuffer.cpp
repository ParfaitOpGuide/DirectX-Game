#include "VertexBuffer.h"
#include "GraphicsEngine.h"
#include "RenderSystem.h"
#include <exception>

VertexBuffer::VertexBuffer(RenderSystem* system, void* list_vertices, UINT size_vertex, UINT size_list, void* shader_byte_code, UINT size_byte_shader) : m_system(system), m_layout(0), m_buffer(0)
{
	if (m_buffer)m_buffer->Release();
	if (m_layout)m_layout->Release();



	D3D11_BUFFER_DESC buff_desc = {};
	buff_desc.Usage = D3D11_USAGE_DEFAULT;
	buff_desc.ByteWidth = size_vertex * size_list;
	buff_desc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	buff_desc.CPUAccessFlags = 0;
	buff_desc.MiscFlags = 0;

	D3D11_SUBRESOURCE_DATA init_data = { };
	init_data.pSysMem = list_vertices;

	m_size_vertex = size_vertex;
	m_size_list = size_list;

	if (FAILED(m_system->m_d3d_device->CreateBuffer(&buff_desc, &init_data, &m_buffer)))
	{
		throw std::exception("VertexBuffer not made");
	}

	D3D11_INPUT_ELEMENT_DESC layout[] =
	{
		{"POSITION", 0,DXGI_FORMAT_R32G32B32_FLOAT, 0, 0,D3D11_INPUT_PER_VERTEX_DATA,0},
		{"TEXCOORD", 0,DXGI_FORMAT_R32G32_FLOAT, 0, 12,D3D11_INPUT_PER_VERTEX_DATA,0},
	};

	UINT size_layout = ARRAYSIZE(layout);

	if (FAILED(m_system->m_d3d_device->CreateInputLayout(layout, size_layout, shader_byte_code, size_byte_shader, &m_layout)))
	{
		throw std::exception("VertexBuffer not made");
	}


}


UINT VertexBuffer::getSizeVertexList()
{
	return this->m_size_list;
}

VertexBuffer::~VertexBuffer()
{
	m_layout->Release();
	m_buffer->Release();
}

