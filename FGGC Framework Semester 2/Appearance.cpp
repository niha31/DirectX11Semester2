#include "Appearance.h"
Appearance::Appearance(Geometry geometry, Material material, ID3D11ShaderResourceView* textureRV)
{
	_geometry = geometry;
	_material = material;
	_textureRV = textureRV;
}

Appearance::Appearance()
{

}
Appearance::~Appearance()
{

}