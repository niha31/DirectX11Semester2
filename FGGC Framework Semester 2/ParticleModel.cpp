#include "ParticleModel.h"
ParticleModel::ParticleModel(Transform* transform, Vector initialVelocity, Vector initialAcceleration, float radius)
{
	_velocity = initialVelocity;
	_acceleration = initialAcceleration;
	_transform = transform;
	_drag = 0.0025f;
	_boundSphere = radius;
	_canMove = false;
	_thrust = Vector(0.0f, 0.0f, 0.0f);
	_springForce = Vector(0.0f, 0.0f, 0.0f);
}

ParticleModel::~ParticleModel()
{

}

void ParticleModel::Update(float t)
{
	// Move gameobject
	//move cube
	_springPosition = Vector(_transform->GetPosition().x, 20.0f, _transform->GetPosition().y);
	_springOriginalLength = _springPosition.distance(_transform->GetPosition());

	if (_canMove)
	{
		if (GetKeyState('W') & 0x8000)
		{
			AddThrust(Vector(0.0f, 0.0f, 0.05f));
		}
		if (GetKeyState('S') & 0x8000)
		{
			AddThrust(Vector(0.0f, 0.0f, -0.05f));

		}
		if (GetKeyState('D') & 0x8000)
		{
			AddThrust(Vector(0.05f, 0.0f, 0.0f));
		}
		if (GetKeyState('A') & 0x8000)
		{
			AddThrust(Vector(-0.05f, 0.0f, 0.0f));
		}

		if (GetKeyState('Q') & 0x8000)
		{

			AddThrust(Vector(0.0f, 0.5f, 0.0f));

		}	
	}

	AddWeight();
	Spring();
	DynamicAcceleration(t);
}

void ParticleModel::UpdateNetForce(const float t)
{
	_netForce = Vector(0.0f, 0.0f, 0.0f);

	_netForce += _thrust;
	_netForce.y -= _gravity;
	_netForce += _springForce;
	
	_thrust = Vector(0.0f, 0.0f, 0.0f);
}

void ParticleModel::UpdateAcceleration()
{
	_acceleration = _netForce / _mass;
}

void ParticleModel::UpdateVelocity(const float t)
{
	_velocity += _acceleration;

	_velocity *= (1.0f - (_drag * t));
}

void ParticleModel::DynamicAcceleration(const float t)
{
	UpdateNetForce(t);
	UpdateAcceleration();
	UpdateVelocity(t);
	//RotateObject(t);
	//UpdateRotation(t);
	UpdatePosition(t);
}

void ParticleModel::UpdatePosition(const float t)
{
	Vector newPos = _transform->GetPosition() + _velocity * t;

	if (newPos.y < 0.5f)
	{
		newPos.y = 0.5f;
	}

	_transform->SetPosition(newPos);
}

void ParticleModel::UpdateRotation(const float t)
{
	_transform->GetQuaternion()->addScaledVector(Vector(0.0f, 0.2f, 0.2f), 0.1f);
	XMStoreFloat4x4(_transform->GetWorldMatrixPointer(), XMMatrixRotationQuaternion(*(_transform->ReturnVectorQuaternion())) * XMMatrixScaling(_transform->GetScale().x, _transform->GetScale().y, _transform->GetScale().z) * XMMatrixRotationY(t / 10) * XMMatrixTranslation(_transform->GetPosition().x, _transform->GetPosition().y, _transform->GetPosition().z));
}

void ParticleModel::SetPosOnPlane()
{
	Vector temp = _transform->GetPosition();
	_transform->SetPosition(temp.x, 0.5f, temp.z);
}


void ParticleModel::AddThrust(Vector force)
{
	_thrust += force;
}

void ParticleModel::Spring()
{
	_spring = _springPosition - _transform->GetPosition();

	float length = _spring.lenth();
	float displacement = length - _springOriginalLength;

	Vector springNormal = _spring.normalization();

	_springForce = (springNormal * (displacement * 100));

}

void ParticleModel::AddWeight()
{
	_weight = _mass * _gravity;
}

void ParticleModel::AddUpThrust()
{
	_upThrust = 0;
	if (_transform->GetPosition().y <= 0.5)
	{

		_upThrust = _weight;
	}
	else
	{
		_upThrust = -_weight;
	}

	_netForce.y = _netForce.y * _upThrust;
}

bool ParticleModel::CollisionCheck(Vector position, float radius)
{
	float distance = _transform->GetPosition().distance(position);

	if (distance > _boundSphere + radius)
	{
		return false;
	}
	else
	{
		return true;
	}
}

void ParticleModel::RotateObject(const float t)
{
	Vector startPosition = _transform->GetPosition();
	Vector endPosition = _transform->GetPosition() + _velocity * t;

	Vector diffrence = endPosition - startPosition;

	float rotation = atan2(diffrence.z, diffrence.x) * 180;

	_rotationVelocity.x = cos(rotation) * 5;
	_rotationVelocity.y = 0.0;
	_rotationVelocity.z = sin(rotation) * 5;
}


