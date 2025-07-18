#pragma once

#include "Vector2D.h"
#include "Vector3D.h"


class VertexMesh
{
public:
	VertexMesh() :m_position(), m_texcoord()
	{

	}

	VertexMesh(Vector3D position, Vector2D tex) : m_position(position), m_texcoord(tex)
	{

	}

	VertexMesh(const VertexMesh& vertex) :m_position(vertex.m_position), m_texcoord(vertex.m_texcoord)
	{

	}

	~VertexMesh()
	{

	}

	Vector3D m_position;
	Vector2D m_texcoord;
};