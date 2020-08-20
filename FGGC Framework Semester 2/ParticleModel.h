#pragma once
#include <d3d11_1.h>
#include <directxmath.h>
#include "Vector.h"
#include "Transform.h"


using namespace DirectX;

class ParticleModel
{
private:
	Vector _velocity;
	Vector _rotationVelocity;
	Vector _acceleration;
	Transform * _transform;
	float _mass = 50.0f;
	float _gravity = 0.035f;
	float _boundSphere;
	bool _canMove;

	//the forces applied on object
	Vector _netForce;
	Vector _breakForce;
	Vector _thrust;
	float _weight;
	float _upThrust;

	Vector _spring;
	float _springOriginalLength;
	Vector _springPosition;
	Vector _springForce;
	float _springK = 50;

	float _drag;

public:
	ParticleModel(Transform* transform, Vector initialVelocity, Vector initialAcceleration, float radius);
	~ParticleModel();

	void Update(float t);

	void SetVelocity(Vector velocity) { _velocity = velocity; }
	Vector GetVelocity() const { return _velocity; }

	void SetAcceleration(Vector acceleration) { _acceleration = acceleration; }
	Vector GetAcceleration() const { return _acceleration; }

	float GetBoundingSphere() const { return _boundSphere; }

	Transform GetTransform() { return *_transform;}

	float GetWeight() const { return _weight; }

	void UpdateNetForce(const float t);
	void UpdateAcceleration();
	void UpdateVelocity(const float t);
	void DynamicAcceleration(const float t);
	void UpdatePosition(const float t);
	void UpdateRotation(const float t);
	void SetPosOnPlane();

	void RotateObject(const float t);

	void AddThrust(Vector force);
	void AddWeight();
	void AddUpThrust();
	void Spring();

	bool CollisionCheck(Vector position, float radius);

	void CanMove() { _canMove = true; }
	void CantMove() { _canMove = false; }
	bool CanItMove() { return _canMove; }
};

