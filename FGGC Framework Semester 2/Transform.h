#pragma once

#include <d3d11_1.h>
#include <directxmath.h>
#include "Vector.h"
#include "Quaternions.h"

using namespace DirectX;

class Transform
{
public:
	Transform();
	Transform(Vector position, Vector rotation, Vector scale);
	~Transform();

	void SetScale(Vector scale) { _scale = scale; }
	void SetScale(float x, float y, float z) { _scale.x = x; _scale.y = y; _scale.z = z; }

	Vector GetScale() const { return _scale; }

	void SetRotation(Vector rotation) { _rotation = rotation; }
	void SetRotation(float x, float y, float z) { _rotation.x = x; _rotation.y = y; _rotation.z = z; }

	Vector GetRotation() const { return _rotation; }

	XMMATRIX GetWorldMatrix() const { return XMLoadFloat4x4(&_world); }
	XMFLOAT4X4* GetWorldMatrixPointer() { return &_world; }
	void SetWorldMatrix(XMMATRIX scale, XMMATRIX rotation, XMMATRIX translation);
	void SetWorldMatrix(XMMATRIX object, XMMATRIX parent);

	//Setters and Getters for position/rotation/scale
	void SetPosition(Vector pos) { _lastPosition = _position; _position = pos; }
	void SetPosition(float x, float y, float z) { _position.x = x; _position.y = y; _position.z = z; }
	Vector GetPosition() const { return _position; }

	void SetLastPosition(Vector pos) { _lastPosition = pos; }
	Vector GetLastPosition() { return _lastPosition; }

	void UpdateTransformMatrix();
	XMMATRIX GetTransfromMatrix() { return _transformMatrix; }

	Quaternion* GetQuaternion() { return _quaternion; }
	XMVECTOR* ReturnVectorQuaternion() {return &(XMVectorSet(_quaternion->i, _quaternion->j, _quaternion->k, _quaternion->r));	}


private:
	Vector _position;
	Vector _rotation;
	Vector _scale;
	XMFLOAT4X4 _world;
	Vector _lastPosition;

	Quaternion* _quaternion;
	XMMATRIX _transformMatrix;
};

