#include "Collision.h"
#include "Math2.h"

void Collision::SetObject(DirectX::XMFLOAT3 cubePos, DirectX::XMFLOAT3 cubeScale)
{
	/*this->cubePos = cubePos;
	this->cubeScale = cubeScale;*/

	//cubeVertex1 setting
	cubeVertex1.c = cubePos;

	//min,maxの
	cubeVertex1.min = { cubePos.x - (cubeScale.x / 2) ,cubePos.y - (cubeScale.y),cubePos.z - (cubeScale.z / 2) };
	cubeVertex1.max = { cubePos.x + (cubeScale.x / 2) ,cubePos.y + (cubeScale.y),cubePos.z + (cubeScale.z / 2) };
}

bool Collision::Update(DirectX::XMFLOAT3 spherePos, DirectX::XMFLOAT3 sphereScale)
{
	/*cubeVertex1.c = cubePos;*/

	//min,maxの
	/*cubeVertex1.min = { cubePos.x - (cubeScale.x * 2) ,cubePos.y - (cubeScale.y * 2),cubePos.z - (cubeScale.z * 2) };
	cubeVertex1.max = { cubePos.x + (cubeScale.x * 2) ,cubePos.y + (cubeScale.y * 2),cubePos.z + (cubeScale.z * 2) };*/
	/*cubeVertex1.min = { cubePos.x - (cubeScale.x *1.5f) ,cubePos.y - (cubeScale.y * 1.5f),cubePos.z - (cubeScale.z * 1.5f) };
	cubeVertex1.max = { cubePos.x + (cubeScale.x *1.5f) ,cubePos.y + (cubeScale.y * 1.5f),cubePos.z + (cubeScale.z * 1.5f) }; */

	//SphereVertex1の値を設定
	sphereVertex1.c = spherePos;
	sphereVertex1.r = sphereScale;
	sphereVertex1.min = { spherePos.x - (sphereScale.x / 2) ,spherePos.y - (sphereScale.y / 2),spherePos.z - (sphereScale.z / 2) };
	sphereVertex1.max = { spherePos.x + (sphereScale.x / 2) ,spherePos.y + (sphereScale.y / 2),spherePos.z + (sphereScale.z / 2) };


	DirectX::XMFLOAT3 v{};
	
	bool xFlag = false;
	bool yFlag = false;
	bool zFlag = false;
	
	if (sphereVertex1.max.x >= cubeVertex1.min.x && sphereVertex1.min.x <= cubeVertex1.max.x)xFlag = true;
	if (sphereVertex1.max.y >= cubeVertex1.min.y && sphereVertex1.min.y <= cubeVertex1.max.y)yFlag = true;
	if (sphereVertex1.max.z >= cubeVertex1.min.z && sphereVertex1.min.z <= cubeVertex1.max.z)zFlag = true;

	//全ての座標が範囲内にあったら当たり
	if (xFlag == true && yFlag == true && zFlag == true)return 1;

	//当たっていない
	return 0;
}