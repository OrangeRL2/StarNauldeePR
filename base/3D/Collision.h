#pragma once
#include "DirectXMath.h"

class Collision
{
private:

	struct CubeVertex
	{
		DirectX::XMFLOAT3 c;
		//DirectX::XMFLOAT3 v[8];
		DirectX::XMFLOAT3 min;	//-x,-y,-z
		DirectX::XMFLOAT3 max;	//x,y,z
	};
	//当たり判定の計算に必要な構造体
	struct SphereVertex
	{
		DirectX::XMFLOAT3 c;	//center
		DirectX::XMFLOAT3 r;	//radius
		DirectX::XMFLOAT3 min;
		DirectX::XMFLOAT3 max;
	};
public:
	//Set objects for collision detection (rectangle and sphere)
	void SetObject(DirectX::XMFLOAT3 cubePos, DirectX::XMFLOAT3 cubeScale);

	bool Update(DirectX::XMFLOAT3 spherePos, DirectX::XMFLOAT3 sphereScale);

	//Getter
	DirectX::XMFLOAT3 GetPosition() { return cubeVertex1.c; }
	DirectX::XMFLOAT3 GetMin() { return cubeVertex1.min; }
	DirectX::XMFLOAT3 GetMax() { return cubeVertex1.max; }
private:
	//collision
	CubeVertex cubeVertex1;
	SphereVertex sphereVertex1;

	/*DirectX::XMFLOAT3 cubePos;
	DirectX::XMFLOAT3 cubeScale;*/

	bool hit;
};

