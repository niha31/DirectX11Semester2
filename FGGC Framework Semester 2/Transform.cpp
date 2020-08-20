#include "Transform.h"
Transform::Transform(Vector position, Vector rotation, Vector scale)
{
	_position = position;
	_lastPosition = position;
	_rotation = rotation;
	_scale = scale;
	

	_quaternion = new Quaternion();
	CalculateTransformMatrix(_transformMatrix, _position, *_quaternion);
}

Transform::Transform()
{

}

Transform::~Transform()
{

}

void Transform::SetWorldMatrix(XMMATRIX scale, XMMATRIX rotation, XMMATRIX translation)
{
	XMStoreFloat4x4(&_world, scale * rotation * translation);
}

void Transform::SetWorldMatrix(XMMATRIX object, XMMATRIX parent)
{
	XMStoreFloat4x4(&_world, object * parent);
}

void Transform::UpdateTransformMatrix()
{
	CalculateTransformMatrix(_transformMatrix, _position, *_quaternion);
}