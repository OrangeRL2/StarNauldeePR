//#include "Enemy.h"
//using namespace DirectX::SimpleMath;
//
//ID3D12Device* Enemy::device = nullptr;
//Camera* Enemy::camera = nullptr;
//Input* Enemy::input = nullptr;
//DXInput* Enemy::dxInput = nullptr;
//const XMFLOAT3 Enemy::rotLimit = { 0.5f, 0.5f, 0.5f };
//void Enemy::Initialize(FbxModel* model, FbxModel* model2)
//{
//	//�I�u�W�F�N�g������
//	object0 = new FbxObject3D;
//	object0->Initialize();
//	object0->SetModel(model);
//	model1 = model2;
//}
//void Enemy::Update(XMFLOAT3 spline)
//{
//
//	if (shotFlag == false)
//	{
//		ShotStraightBullet();
//		shotTimer = 100;
//		shotFlag = true;
//	}
//	if (shotTimer > 0) {
//		shotTimer--;
//		if (shotTimer == 0) {
//			shotFlag = false;
//		}
//	}
//	for (std::unique_ptr<FbxObject3D>& object0 : objects)
//	{
//		object0->Update();
//
//		Vector3 velocity;
//		velocity = { 1,0,10 };
//		bulletPos.x += velocity.x;
//		//�z�u
//		object0->SetPosition(bulletPos);
//	}
//
//	//�I�u�W�F�N�g�X�V
//	finalPos = XMFLOAT3{ spline.x + position0.x,
//						 spline.y + position0.y ,
//						 spline.z + position0.z };
//	object0->SetPosition(finalPos);
//	object0->SetScale({ scale0 });
//	object0->SetRotation({ rotation0 });
//
//	object0->Update();
//
//	/*if (input->PushKey(DIK_SPACE))
//	{
//		ShotStraightBullet();
//	}*/
//
//	//bullets_.remove_if([](std::unique_ptr<PlayerBullet>& bullet) {
//	//	//return bullet->IsDead();
//	//	});
//	/*for (std::unique_ptr<PlayerBullet>& bullet : bullets_) {
//		bullet->Update(finalPos);
//	}*/
//}
//
//void Enemy::Draw(ID3D12GraphicsCommandList* cmdList)
//{
//	object0->Draw(cmdList);
//
//	for (std::unique_ptr<FbxObject3D>& object0 : objects)
//	{
//		object0->Draw(cmdList);
//	}
//}
//
//
//void Enemy::EnemyMove()
//{
//
//	if (input->PushKey(DIK_W))
//	{
//
//		position0.y += velocity0.y;
//		centerpos.y += 0.4f;
//		rotation0.z -= 0.05f;
//
//	}
//	if (input->PushKey(DIK_S))
//	{
//		if (position0.y >= -11.0f) {
//			position0.y -= velocity0.y;
//			centerpos.y -= 0.4f;
//			rotation0.z += 0.05f;
//		}
//	}
//	if (input->PushKey(DIK_D))
//	{
//		if (position0.z <= 15.0f) {
//			position0.z += velocity0.z;
//			centerpos.y += 0.4f;
//			rotation0.x += 0.1f;
//		}
//
//	}
//	if (input->PushKey(DIK_A))
//	{
//		if (position0.z >= -15.0f) {
//			position0.z -= velocity0.z;
//			centerpos.z -= 0.4f;
//			rotation0.x -= 0.1f;
//		}
//	}
//	if (rotation0.z >= -0.0f) {
//		rotation0.z -= 0.02f;
//	}
//	else if (rotation0.z <= 0.5f) {
//		rotation0.z += 0.02f;
//	}
//	if (rotation0.x <= 0.0f) {
//		rotation0.x += 0.02f;
//	}
//	if (rotation0.x >= 0.0f) {
//		rotation0.x -= 0.02f;
//	}
//
//	//�p�x�̌��E�l����͂ݏo���Ȃ�
//	rotation0.y = max(rotation0.y, -rotLimit.y);
//	rotation0.y = min(rotation0.y, +rotLimit.y);
//	rotation0.x = max(rotation0.x, -rotLimit.x);
//	rotation0.x = min(rotation0.x, +rotLimit.x);
//	rotation0.z = max(rotation0.z, -rotLimit.z);
//	rotation0.z = min(rotation0.z, +rotLimit.z);
//
//}
//
//void Enemy::CameraFollow()
//{
//	////���@���X���Ă���p�x�Ɉړ�������
//	//XMFLOAT3 velocity = { 0, 0, 0 };
//	//velocity.x = 0.4 * (rotation0.y / rotLimit.y);
//	//velocity.y = 0.4 * -(rotation0.x / rotLimit.x);
//	//position0.x += velocity.x;
//	//position0.y += velocity.y;
//	//position0.z += velocity.z;
//}
//
//void Enemy::Rotate(XMFLOAT3 targetPos)
//{
//	Quaternion q;
//
//	targetPos = XMFLOAT3(10, 10000, 1);
//	q.RotateTowards(XMFLOAT4{ 0,0,0,0 }, 10);
//
//	//�p�x�̌��E�l����͂ݏo���Ȃ�
//	rotation0.y = max(rotation0.y, -rotLimit.y);
//	rotation0.y = min(rotation0.y, +rotLimit.y);
//	rotation0.x = max(rotation0.x, -rotLimit.x);
//	rotation0.x = min(rotation0.x, +rotLimit.x);
//}
//
//void Enemy::ShotStraightBullet()
//{
//	std::unique_ptr<FbxObject3D>newObject = std::make_unique<FbxObject3D>();
//
//	newObject->Initialize();
//	////�e�̑��x��ݒ�
//	const float bulletSpeed = 6;
//
//	newObject->SetModel(model1);
//
//	//�I�u�W�F�N�g�X�V
//	bulletPos = { finalPos.x,finalPos.y,finalPos.z };
//	//�z�u
//	newObject->SetPosition(bulletPos);
//	newObject->SetScale({ scale0 });
//	newObject->SetRotation({ rotation0 });
//
//	objects.push_back(std::move(newObject));
//
//}
