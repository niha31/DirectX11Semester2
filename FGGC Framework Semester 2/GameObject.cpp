#include "GameObject.h"

GameObject::GameObject(string type, Transform * transform, Appearance* appearance): _type(type)
{
	_parent = nullptr;
	_type = type;
	float radius = 0;

	if (type == "Cube")
	{
		radius = 0.5f;//1.732050f;
	}
	
	_transform = new Transform(transform->GetPosition(), transform->GetRotation(), transform->GetScale());
	_particleModel = new ParticleModel(_transform, Vector(0.0f, 0.0f, 0.0f), Vector(0.0f, 0.0f, 0.0f), radius);
	_appearance = new Appearance(appearance->GetGeometryData(), appearance->GetMaterial(), appearance->GetTextureRV());
}

GameObject::~GameObject()
{
}

Transform * GameObject::GetTransform() const
{
	return _transform;
}

ParticleModel* GameObject::GetParticleModel() const
{
	return _particleModel;
}

Appearance* GameObject::GetAppearance() const
{
	return _appearance;
}

void GameObject::Update(float t)
{
	if (_type == "Cube")
	{
		_particleModel->Update(t);
	}


	// Calculate world matrix
	XMMATRIX scale = XMMatrixScaling(_transform->GetScale().x, _transform->GetScale().y, _transform->GetScale().z);
	XMMATRIX rotation = XMMatrixRotationX(_transform->GetRotation().x) * XMMatrixRotationY(_transform->GetRotation().y) * XMMatrixRotationZ(_transform->GetRotation().z);
	XMMATRIX translation = XMMatrixTranslation(_transform->GetPosition().x, _transform->GetPosition().y, _transform->GetPosition().z);

	_transform->SetWorldMatrix(scale, rotation, translation);

	if (_parent != nullptr)
	{
		_transform->SetWorldMatrix(_transform->GetWorldMatrix(), _parent->GetTransform()->GetWorldMatrix());
	}
}

void GameObject::Draw(ID3D11DeviceContext * pImmediateContext)
{
	// NOTE: We are assuming that the constant buffers and all other draw setup has already taken place
	Geometry _geometry = _appearance->GetGeometryData();
	// Set vertex and index buffers

	pImmediateContext->IASetVertexBuffers(0, 1, &_geometry.vertexBuffer, &_geometry.vertexBufferStride, &_geometry.vertexBufferOffset);
	pImmediateContext->IASetIndexBuffer(_geometry.indexBuffer, DXGI_FORMAT_R16_UINT, 0);

	pImmediateContext->DrawIndexed(_geometry.numberOfIndices, 0, 0);
}
