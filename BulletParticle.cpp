#include "BulletParticle.h"
#include "FbxLoader.h"
using namespace DirectX::SimpleMath;

ID3D12Device* BulletParticle::device = nullptr;
Camera* BulletParticle::camera = nullptr;
Input* BulletParticle::input = nullptr;
DXInput* BulletParticle::dxInput = nullptr;
const XMFLOAT3 BulletParticle::rotLimit = { 0.5f, 0.5f, 0.5f };
void BulletParticle::Initialize(FbxModel* model, XMFLOAT3 parent)
{
	object0 = new FbxObject3D;
	object0->Initialize();
	object0->SetModel(model);

	finalPos = XMFLOAT3{ parent.x ,
						 parent.y  ,
						 parent.z };

	
}
void BulletParticle::Update()
{
	float speed = 0.0003f;

	if (scale0.y >= 0.0f) {
	
		scale0.y -= speed;
		scale0.z -= speed;
		}
		

	if (scale0.x <= 0) {
		SetDeath();
	}
	object0->SetPosition(finalPos);
	object0->SetScale({ scale0 });
	object0->SetRotation({ rotation0 });

	object0->Update();

}

void BulletParticle::Draw(ID3D12GraphicsCommandList* cmdList)
{
	if (isDead == false) {
		object0->Draw(cmdList);
	}
}