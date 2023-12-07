#include "EnemyBullet.h"
#include "FbxLoader.h"
using namespace DirectX::SimpleMath;

ID3D12Device* EnemyBullet::device = nullptr;
Camera* EnemyBullet::camera = nullptr;
Input* EnemyBullet::input = nullptr;
DXInput* EnemyBullet::dxInput = nullptr;
const XMFLOAT3 EnemyBullet::rotLimit = { 0.5f, 0.5f, 0.5f };
void EnemyBullet::Initialize(FbxModel* model, XMFLOAT3 parent, XMFLOAT3 playerPos)
{
	PlayerAim(parent, playerPos);
	object0 = new FbxObject3D;
	object0->Initialize();
	object0->SetModel(model);
	model0 = model;
	finalPos = XMFLOAT3{ parent.x ,
						 parent.y  ,
						 parent.z };
}
void EnemyBullet::Update()
{

	if (particleFlag == true) {
		deathTime += 1;
		if (deathTime >= 50) {
			SetDeath();
		}
	}
	Vector3 velocity;
	velocity = { 2,0,10 };
	if (particleFlag == false) {
		finalPos.x -= position1.x;
		finalPos.y -= position1.y;
		finalPos.z -= position1.z;
	}
	object0->SetPosition(finalPos);
	object0->SetScale({ scale0 });
	object0->SetRotation({ rotation0 });

	object0->Update();

	for (std::unique_ptr<Particle>& object0 : particles)
	{
		object0->Update();
	}
}

void EnemyBullet::Draw(ID3D12GraphicsCommandList* cmdList)
{
	if (particleFlag == false) {
		object0->Draw(cmdList);
	}
	for (std::unique_ptr<Particle>& object0 : particles)
	{
		object0->Draw(cmdList);
	}
}

void EnemyBullet::ParticleInitialize()
{
	std::unique_ptr<Particle>newObject = std::make_unique<Particle>();

	particlePos = { finalPos.x,finalPos.y,finalPos.z };

	newObject->Initialize(model0, particlePos);

	particles.push_back(std::move(newObject));
}
void EnemyBullet::Collision()
{
	if (particleFlag == false)
	{
		for (int i = 0; i < 10; i++) {
			ParticleInitialize();
		}
		particleFlag = true;
	}
}
void EnemyBullet::PlayerAim(XMFLOAT3 enemy, XMFLOAT3 player)
{
	const float speed = 1.0f;
	posA = XMLoadFloat3(&enemy);
	posB = XMLoadFloat3(&player);
	posC = posA - posB;
	posD=XMVector3Normalize(posC);
	posD *= speed;
	XMStoreFloat3(&position1, posD);
}