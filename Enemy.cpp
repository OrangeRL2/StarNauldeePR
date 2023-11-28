#include "Enemy.h"
using namespace DirectX::SimpleMath;

ID3D12Device* Enemy::device = nullptr;
Camera* Enemy::camera = nullptr;
Input* Enemy::input = nullptr;
DXInput* Enemy::dxInput = nullptr;
const XMFLOAT3 Enemy::rotLimit = { 0.5f, 0.5f, 0.5f };

//乱数シード生成器
std::random_device seed_gen;
//メルセンヌ・ツイスターの乱数エンジン
std::mt19937_64 engine(seed_gen());
//乱数範囲の指定
std::uniform_real_distribution<float> distRot(MathFunc::Utility::Deg2Rad(-60), MathFunc::Utility::Deg2Rad(60));
void Enemy::Initialize(FbxModel* model, FbxModel* model2)
{
	//�I�u�W�F�N�g������
	object0 = new FbxObject3D;
	object0->Initialize();
	object0->SetModel(model);
	model0 = model;
	model1 = model2;

}
void Enemy::Update(XMFLOAT3 spline)
{
	if (particleFlag == true) {
		time += 1;
		if (time >= 100) {
			IsDead();
		}
	}

	if (shotFlag == false)
	{
		ShotStraightBullet();
		shotTimer = 500;
		shotFlag = true;
	}
	if (shotTimer > 0) {
		shotTimer--;
		if (shotTimer == 0) {
			shotFlag = false;
		}
	}
	for (std::unique_ptr<FbxObject3D>& object0 : objects)
	{
		object0->Update();

		XMFLOAT3 velocity;
		velocity = { 1,0,10 };
		bulletPos.x += velocity.x;
		//�z�u
		object0->SetPosition(bulletPos);
	}
	
	for (std::unique_ptr<Particle>& object0 : particles)
	{
		object0->Update();
	}

	objects.remove_if([](std::unique_ptr<FbxObject3D>& object0) {
		return object0->GetDeath();
		});
	//�I�u�W�F�N�g�X�V
	finalPos = XMFLOAT3{ spline.x + position0.x,
						 spline.y + position0.y ,
						 spline.z + position0.z };
	object0->SetPosition(position0);
	object0->SetScale({ scale0 });
	object0->SetRotation({ rotation0 });

	object0->Update();
	
	/*if (input->PushKey(DIK_SPACE))
	{
		ShotStraightBullet();
	}*/

	//bullets_.remove_if([](std::unique_ptr<PlayerBullet>& bullet) {
	//	//return bullet->IsDead();
	//	});
	/*for (std::unique_ptr<PlayerBullet>& bullet : bullets_) {
		bullet->Update(finalPos);
	}*/
}

void Enemy::Draw(ID3D12GraphicsCommandList* cmdList)
{
	if (particleFlag == false) {
	object0->Draw(cmdList);
	}
	
	for (std::unique_ptr<FbxObject3D>& object0 : objects)
	{
		object0->Draw(cmdList);
	}

	for (std::unique_ptr<Particle>& object0 : particles)
	{
		object0->Draw(cmdList);
	}
}


void Enemy::EnemyMove()
{

	if (input->PushKey(DIK_W))
	{

		position0.y += velocity0.y;
		centerpos.y += 0.4f;
		rotation0.z -= 0.05f;

	}
	if (input->PushKey(DIK_S))
	{
		if (position0.y >= -11.0f) {
			position0.y -= velocity0.y;
			centerpos.y -= 0.4f;
			rotation0.z += 0.05f;
		}
	}
	if (input->PushKey(DIK_D))
	{
		if (position0.z <= 15.0f) {
			position0.z += velocity0.z;
			centerpos.y += 0.4f;
			rotation0.x += 0.1f;
		}

	}
	if (input->PushKey(DIK_A))
	{
		if (position0.z >= -15.0f) {
			position0.z -= velocity0.z;
			centerpos.z -= 0.4f;
			rotation0.x -= 0.1f;
		}
	}
	if (rotation0.z >= -0.0f) {
		rotation0.z -= 0.02f;
	}
	else if (rotation0.z <= 0.5f) {
		rotation0.z += 0.02f;
	}
	if (rotation0.x <= 0.0f) {
		rotation0.x += 0.02f;
	}
	if (rotation0.x >= 0.0f) {
		rotation0.x -= 0.02f;
	}

	//�p�x�̌��E�l����͂ݏo���Ȃ�
	rotation0.y = max(rotation0.y, -rotLimit.y);
	rotation0.y = min(rotation0.y, +rotLimit.y);
	rotation0.x = max(rotation0.x, -rotLimit.x);
	rotation0.x = min(rotation0.x, +rotLimit.x);
	rotation0.z = max(rotation0.z, -rotLimit.z);
	rotation0.z = min(rotation0.z, +rotLimit.z);

}

void Enemy::CameraFollow()
{
	////���@���X���Ă���p�x�Ɉړ�������
	//XMFLOAT3 velocity = { 0, 0, 0 };
	//velocity.x = 0.4 * (rotation0.y / rotLimit.y);
	//velocity.y = 0.4 * -(rotation0.x / rotLimit.x);
	//position0.x += velocity.x;
	//position0.y += velocity.y;
	//position0.z += velocity.z;
}

void Enemy::Rotate()
{
	std::unique_ptr<Particle>newObject = std::make_unique<Particle>();

	particlePos = { position0.x,position0.y,position0.z };

	newObject->Initialize(model0, particlePos);

	particles.push_back(std::move(newObject));
}

void Enemy::ShotStraightBullet()
{
	std::unique_ptr<FbxObject3D>newObject = std::make_unique<FbxObject3D>();

	newObject->Initialize();
	////�e�̑��x��ݒ�
	const float bulletSpeed = 6;

	newObject->SetModel(model1);

	//�I�u�W�F�N�g�X�V
	bulletPos = { position0.x,position0.y,position0.z };
	//�z�u
	newObject->SetPosition(bulletPos);
	newObject->SetScale({ scale0 });
	newObject->SetRotation({ rotation0 });

	objects.push_back(std::move(newObject));

}

void Enemy::Collision()
{
	for (std::unique_ptr<FbxObject3D>& object0 : objects)
	{
		object0->SetDeath();
	}

}

void Enemy::CollisionParticle()
{
	if(particleFlag == false)
	{
	for (int i = 0; i < 10; i++) {
		Rotate();
	}
	particleFlag = true;
	}
}

void Enemy::revive()
{
	isDead = false;
	particleFlag = false;
}