#include "PlayerBullet.h"
#include "FbxLoader.h"
using namespace DirectX::SimpleMath;

ID3D12Device* PlayerBullet::device = nullptr;
Camera* PlayerBullet::camera = nullptr;
Input* PlayerBullet::input = nullptr;
DXInput* PlayerBullet::dxInput = nullptr;
const XMFLOAT3 PlayerBullet::rotLimit = { 0.5f, 0.5f, 0.5f };
void PlayerBullet::Initialize(FbxModel* model, XMFLOAT3 parent, XMFLOAT3 reticle)
{
	object0 = new FbxObject3D;
	object0->Initialize();
	object0->SetModel(model);

	finalPos = XMFLOAT3{ parent.x ,
						 parent.y  ,
						 parent.z };
	
	centerpos = reticle;

	ReticleAim(parent, reticle);
}
void PlayerBullet::Update(XMFLOAT3 reticle)
{
	Vector3 velocity;
	velocity = { 2,0,10 };

	/*finalPos.x -= centerpos.x;
	finalPos.y -= centerpos.y;
	finalPos.z -= centerpos.z;*/
	float distanceThreshold = 1.0f; // You can adjust this threshold as needed
	//player1がplayer0についていく処理
	reticle.x + 200.0f;
	XMVECTOR player0 = XMLoadFloat3(&reticle);
	XMVECTOR player1 = XMLoadFloat3(&finalPos);
	float distance = XMVectorGetX(XMVector3Length(player0 - player1));

	XMVECTOR direction = XMVector3Normalize(player0 - player1);
	player1 = player1 + direction*2;
	XMStoreFloat3(&finalPos, player1);

	if (finalPos.x < reticle.x)
	{
		SetDeath();
	}
	object0->SetPosition(finalPos);
	object0->SetScale({ scale0 });
	object0->SetRotation({ rotation0 });

	ReticleAim(finalPos, reticle);
	object0->Update();

}

void PlayerBullet::Draw(ID3D12GraphicsCommandList* cmdList)
{
	if (isDead == false) {
		object0->Draw(cmdList);
	}

}

void PlayerBullet::BulletShot()
{

}
void PlayerBullet::ReticleAim(XMFLOAT3 player, XMFLOAT3 reticle)
{
	/*const float speed = 1.0f;
	posA = XMLoadFloat3(&player);
	posB = XMLoadFloat3(&reticle);
	posC = posA - posB;
	posD = XMVector3Normalize(posC);
	posD *= speed;
	XMStoreFloat3(&position1, posD);
	position1.x *= speed;
	position1.y *= speed;
	position1.z *= speed;*/


	//player1がplayer0についていく処理
	//XMVECTOR player0 = XMLoadFloat3(&player);
	//XMVECTOR player1 = XMLoadFloat3(&reticle);
	//float distance = XMVectorGetX(XMVector3Length(player1 - player0));

	//XMVECTOR direction = XMVector3Normalize(player0 - player1);
	//player1 = player1 + direction / 1;
	//XMStoreFloat3(&finalPos, player0);

}