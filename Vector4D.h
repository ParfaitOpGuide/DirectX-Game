#pragma once




class Vector4D
{
public:
	Vector4D() :m_x(0), m_y(0), m_z(0), m_w(0)
	{

	}

	Vector4D(float x, float y, float z, float w) :m_x(x), m_y(y), m_z(z), m_w(w)
	{

	}

	Vector4D(const Vector4D& vector) :m_x(vector.m_x), m_y(vector.m_y), m_z(vector.m_z), m_w(vector.m_w)
	{

	}



	~Vector4D()
	{

	}

	float m_x, m_y, m_z, m_w;
};