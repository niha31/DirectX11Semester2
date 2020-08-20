#include "ParticleSystem.h"

ParticleSystem::ParticleSystem(Transform *transform, Appearance *appearance)
{
	_transform = new Transform(transform->GetPosition(), transform->GetRotation(), transform->GetScale());
	_appearance = new Appearance(appearance->GetGeometryData(), appearance->GetMaterial(), appearance->GetTextureRV());
	_lifeSpan = LIFE_SPAN_TIME;
	 UpdateVelocity();
}

ParticleSystem::~ParticleSystem()
{

}

void ParticleSystem::CreateParticle()
{
	
}

void ParticleSystem::DistroyParticle()
{

}

void ParticleSystem::Update(float deltaTime)
{
	//UpdateVelocity(deltaTime);
	//UpdateAcceleration();
	_lifeSpan -= 2.0f;

	// Calculate world matrix
	XMMATRIX scale = XMMatrixScaling(_transform->GetScale().x, _transform->GetScale().y, _transform->GetScale().z);
	XMMATRIX rotation = XMMatrixRotationX(_transform->GetRotation().x) * XMMatrixRotationY(_transform->GetRotation().y) * XMMatrixRotationZ(_transform->GetRotation().z);
	XMMATRIX translation = XMMatrixTranslation(_transform->GetPosition().x, _transform->GetPosition().y, _transform->GetPosition().z);

	_transform->SetWorldMatrix(scale, rotation, translation);

	if (!isDead())
	{
		UpdatePosition(deltaTime);
	}
}

void ParticleSystem::Draw(ID3D11DeviceContext* pImmediateContext)
{
	// NOTE: We are assuming that the constant buffers and all other draw setup has already taken place
	Geometry _geometry = _appearance->GetGeometryData();

	// Set vertex and index buffers
	pImmediateContext->IASetVertexBuffers(0, 1, &_geometry.vertexBuffer, &_geometry.vertexBufferStride, &_geometry.vertexBufferOffset);
	pImmediateContext->IASetIndexBuffer(_geometry.indexBuffer, DXGI_FORMAT_R16_UINT, 0);

	pImmediateContext->DrawIndexed(_geometry.numberOfIndices, 0, 0);
}

void ParticleSystem::UpdateVelocity()
{
	float x = ((rand() % 20) / 10.0) * 2 - 1;
	float z = ((rand() % 20) / 10.0) * 2 - 1;
	float y = ((rand() % 20) / 10.0) * 2 - 1;
	_velocity = Vector(x, y, z);

}

void ParticleSystem::UpdateAcceleration()
{
	_acceleration = Vector(0.0f, 0.5f ,0.0f);
}

bool ParticleSystem::isDead()
{
	if (_lifeSpan < 0.0f)
	{
		return true;
	}
	else
	{
		return false;
	}
}

void ParticleSystem::UpdatePosition(const float t)
{
	Vector newPos = _transform->GetPosition() + _velocity;
	_transform->SetPosition(newPos);
}
