#include "Camera.h"


Camera::Camera()
{
	this->pos = XMFLOAT3(0.0f, 0.0f, 0.0f);
	this->posVector = XMLoadFloat3(&this->pos);
	this->rot = XMFLOAT3(0.0f, 0.0f, 0.0f);
	this->rotVector = XMLoadFloat3(&this->rot);
	this->UpdateViewMatrix();
}

void Camera::SetProjectionValues(float fovDegrees, float aspectRatio, float nearZ, float farZ)
{
	float fovRadians = (fovDegrees / 360.0f) * XM_2PI;
	this->projectionMatrix = XMMatrixPerspectiveFovLH(fovRadians, aspectRatio, nearZ, farZ);
}

const Matrix4x4& Camera::GetViewMatrix4()
{

	XMFLOAT4X4 tmp;
	XMStoreFloat4x4(&tmp, this->viewMatrix);

	Matrix4x4 out;
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			out.m_mat[i][j] = tmp.m[i][j];
		}
	}
	return out;
}
const Matrix4x4& Camera::GetProjectionMatrix4()
{
	XMFLOAT4X4 tmp;
	XMStoreFloat4x4(&tmp, this->projectionMatrix);

	Matrix4x4 out;
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			out.m_mat[i][j] = tmp.m[i][j];
		}
	}
	return out;
}

void Camera::SetPosition(const XMVECTOR& pos)
{
	XMStoreFloat3(&this->pos, pos);
	this->posVector = pos;
	this->UpdateViewMatrix();
}

void Camera::SetPosition(float x, float y, float z)
{
	this->pos = XMFLOAT3(x, y, z);
	this->posVector = XMLoadFloat3(&this->pos);
	this->UpdateViewMatrix();
}

Vector3D Camera::getPosition()
{
	Vector3D out;
	
	out.m_x = this->pos.x;
	out.m_y = this->pos.y;
	out.m_z = this->pos.z;

	return out;
}

void Camera::SetRotation(const XMVECTOR& rot)
{
	this->rotVector = rot;
	XMStoreFloat3(&this->rot, rot);
	this->UpdateViewMatrix();
}

void Camera::SetRotation(float x, float y, float z)
{
	this->rot = XMFLOAT3(x, y, z);
	this->rotVector = XMLoadFloat3(&this->rot);
	this->UpdateViewMatrix();
}

Vector3D Camera::getRotation()
{

	Vector3D out;

	out.m_x = this->rot.x;
	out.m_y = this->rot.y;
	out.m_z = this->rot.z;

	return out;
	
}

const XMVECTOR& Camera::GetForwardVector()
{
	return this->vec_forward;
}

const XMVECTOR& Camera::GetRightVector()
{
	return this->vec_right;
}

const XMVECTOR& Camera::GetBackwardVector()
{
	return this->vec_backward;
}

const XMVECTOR& Camera::GetLeftVector()
{
	return this->vec_left;
}

void Camera::AdjustPosition(float x, float y, float z)
{
	this->pos.x += x;
	this->pos.y += y;
	this->pos.z += z;
	this->posVector = XMLoadFloat3(&this->pos);
	this->UpdateViewMatrix();
}

void Camera::AdjustRotation(float x, float y, float z)
{
	this->rot.x += x;
	this->rot.y += y;
	this->rot.z += z;
	this->rotVector = XMLoadFloat3(&this->rot);
	this->UpdateViewMatrix();
}

void Camera::UpdateViewMatrix()
{
	XMMATRIX camRotationMatrix = XMMatrixRotationRollPitchYaw(this->rot.x, this->rot.y, this->rot.z);
	XMVECTOR camTarget = XMVector3TransformCoord(this->FORWARD, camRotationMatrix);
	camTarget += this->posVector;
	XMVECTOR upDir = XMVector3TransformCoord(this->UP, camRotationMatrix);
	this->viewMatrix = XMMatrixLookAtLH(this->posVector, camTarget, upDir);

	//camera doohick
	XMMATRIX vecRotationMatrix = XMMatrixRotationRollPitchYaw(0.0f, this->rot.y, 0.0f);
	this->vec_forward = XMVector3TransformCoord(this->FORWARD, vecRotationMatrix);
	this->vec_backward = XMVector3TransformCoord(this->BACKWARD, vecRotationMatrix);
	this->vec_left = XMVector3TransformCoord(this->LEFT, vecRotationMatrix);
	this->vec_right = XMVector3TransformCoord(this->RIGHT, vecRotationMatrix);
}