#pragma once

#include <directxmath.h>
#include <d3d11_1.h>
#include <string>
#include "Transform.h"
#include "ParticleModel.h"
#include "Appearance.h"
#include "Vector.h"
#include "Quaternions.h"
#include "ParticleSystem.h"

using namespace DirectX;
using namespace std;

class GameObject
{
public:
	GameObject(string type, Transform * transform, Appearance * appearance);
	~GameObject();

	string GetType() const { return _type; }

	void SetParent(GameObject * parent) { _parent = parent; }

	void Update(float t);
	void Draw(ID3D11DeviceContext * pImmediateContext);

	Transform * GetTransform() const;
	ParticleModel* GetParticleModel() const;
	Appearance* GetAppearance() const;


private:

	string _type;

	GameObject * _parent;

	Transform* _transform;
	ParticleModel* _particleModel;
	Appearance* _appearance;
};

