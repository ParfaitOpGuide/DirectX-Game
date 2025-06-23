#pragma once
#include <DirectXMath.h>
#include "Matrix4x4.h"
#include "Vector3D.h"
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

	Vector3D getPosition();

	void SetRotation(const XMVECTOR& rot);
	void SetRotation(float x, float y, float z);

	Vector3D getRotation();

	const XMVECTOR& GetForwardVector();
	const XMVECTOR& GetRightVector();
	const XMVECTOR& GetBackwardVector();
	const XMVECTOR& GetLeftVector();


	void AdjustPosition(float x, float y, float z);
	void AdjustRotation(float x, float y, float z);



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
	const XMVECTOR BACKWARD = XMVectorSet(0.0f, 0.0f, -1.0f, 0.0f);
	const XMVECTOR LEFT = XMVectorSet(-1.0f, 0.0f, 0.0f, 0.0f);
	const XMVECTOR RIGHT = XMVectorSet(1.0f, 0.0f, 0.0f, 0.0f);
	XMVECTOR vec_forward;
    XMVECTOR vec_left;
	XMVECTOR vec_right;
	XMVECTOR vec_backward;
};