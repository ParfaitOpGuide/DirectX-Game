#pragma once
#include <DirectXMath.h>
#include "Matrix4x4.h"
using namespace DirectX;

class Camera
{
public:
	Camera();
	void SetProjectionValues(float fovDegrees, float aspectRatio, float nearZ, float farZ);

	const Matrix4x4& GetViewMatrix4();
	const Matrix4x4& GetProjectionMatrix4();

	void SetPosition(const XMVECTOR& pos);
	void SetPosition(float x, float y, float z);
	void SetRotation(const XMVECTOR& rot);
	void SetRotation(float x, float y, float z);
private:
	void UpdateViewMatrix();
	XMVECTOR posVector;
	XMVECTOR rotVector;
	XMFLOAT3 pos;
	XMFLOAT3 rot;
	XMMATRIX viewMatrix;
	XMMATRIX projectionMatrix;

	const XMVECTOR FORWARD = XMVectorSet(0.0f, 0.0f, 1.0f, 0.0f);
	const XMVECTOR UP = XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f);
};