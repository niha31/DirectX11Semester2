#pragma once

#include <directxmath.h>
#include <d3d11_1.h>
#include "Vector.h"
#include "GameObject.h"


using namespace DirectX;
using namespace std;

#define LIFE_SPAN_TIME 150

class ParticleSystem
{
private:

	Transform* _transform;
	Appearance* _appearance;

	Vector _velocity;
	Vector _acceleration;
	float _weight;

	float _lifeSpan;
public:
	ParticleSystem(Transform* transform, Appearance* appearance);
	~ParticleSystem();

	void CreateParticle();
	void DistroyParticle();
	void Update(float deltaTime);
	void UpdateVelocity();
	void UpdateAcceleration();
	bool isDead();
	void UpdatePosition(const float t);

	Transform* GetTransform() { return _transform; }
	Appearance* GetAppearance() { return _appearance; }

	void ResetLifeSpan() { _lifeSpan = LIFE_SPAN_TIME; }
	void Draw(ID3D11DeviceContext* pImmediateContext);
};

