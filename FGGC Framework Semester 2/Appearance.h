#pragma once
#include <d3d11_1.h>
#include <directxmath.h>

using namespace DirectX;

struct Geometry
{
	ID3D11Buffer* vertexBuffer;
	ID3D11Buffer* indexBuffer;
	int numberOfIndices;

	UINT vertexBufferStride;
	UINT vertexBufferOffset;
};

struct Material
{
	XMFLOAT4 diffuse;
	XMFLOAT4 ambient;
	XMFLOAT4 specular;
	float specularPower;
};

class Appearance
{
public:
	Appearance(Geometry geometry, Material material, ID3D11ShaderResourceView* _textureRV);
	Appearance();
	~Appearance();


	Geometry GetGeometryData() const { return _geometry; }
	void SetGeometry(Geometry geometry) { _geometry = geometry; };

	Material GetMaterial() const { return _material; }
	void SetMaterial(Material material) { _material = material; };

	void SetTextureRV(ID3D11ShaderResourceView* textureRV) { _textureRV = textureRV; }
	ID3D11ShaderResourceView* GetTextureRV() const { return _textureRV; }
	bool HasTexture() const { return _textureRV ? true : false; }

private:

	Geometry _geometry;
	Material _material;

	ID3D11ShaderResourceView* _textureRV;
};

