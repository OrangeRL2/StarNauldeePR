#include "PlayerBullet.h"
#include "FbxLoader.h"
using namespace DirectX::SimpleMath;

ID3D12Device* PlayerBullet::device = nullptr;
Camera* PlayerBullet::camera = nullptr;
Input* PlayerBullet::input = nullptr;
DXInput* PlayerBullet::dxInput = nullptr;
const XMFLOAT3 PlayerBullet::rotLimit = { 0.5f, 0.5f, 0.5f };
void PlayerBullet::Initialize(FbxModel* model, XMFLOAT3 parent)
{

	object0 = new FbxObject3D;
	object0->Initialize();
	object0->SetModel(model);

	finalPos = XMFLOAT3{ parent.x ,
						 parent.y  ,
						 parent.z };
}
void PlayerBullet::Update()
{
	Vector3 velocity;
	velocity = { 2,0,10 };
	
	finalPos.x-=velocity.x;
	object0->SetPosition(finalPos);
	object0->SetScale({ scale0 });
	object0->SetRotation({ rotation0 });

	object0->Update();
}

void PlayerBullet::Draw(ID3D12GraphicsCommandList* cmdList)
{
	object0->Draw(cmdList);
}

void PlayerBullet::BulletShot()
{

}
