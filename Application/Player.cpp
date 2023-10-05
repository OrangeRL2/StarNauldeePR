#include "Player.h"

ID3D12Device* Player::device = nullptr;
Camera* Player::camera = nullptr;
Input* Player::input = nullptr;
DXInput* Player::dxInput = nullptr;
const XMFLOAT3 Player::rotLimit = { 0.5f, 0.5f, 0.5f };
void Player::Initialize(FbxModel* model)
{
	object0 = new FbxObject3D;
	object0->Initialize();
	object0->SetModel(model);
}
void Player::Update(XMFLOAT3 spline)
{
	PlayerRotate();
	PlayerMove();
	//UpdateCollision();

	finalPos = XMFLOAT3{ spline.x + position0.x,
						 spline.y + position0.y ,
						 spline.z + position0.z };
	finalRotation = XMFLOAT3{ frame + rotation0.x,
								0 + rotation0.y ,
								0 + rotation0.z };
	object0->SetPosition(finalPos);
	object0->SetScale({ scale0 });
	object0->SetRotation({ finalRotation });

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

void Player::Draw(ID3D12GraphicsCommandList* cmdList)
{
	object0->Draw(cmdList);

}


void Player::PlayerMove()
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
	rotation0.y = max(rotation0.y, -rotLimit.y);
	rotation0.y = min(rotation0.y, +rotLimit.y);
	rotation0.x = max(rotation0.x, -rotLimit.x);
	rotation0.x = min(rotation0.x, +rotLimit.x);
	rotation0.z = max(rotation0.z, -rotLimit.z);
	rotation0.z = min(rotation0.z, +rotLimit.z);

}

void Player::CameraFollow()
{

	//XMFLOAT3 velocity = { 0, 0, 0 };
	//velocity.x = 0.4 * (rotation0.y / rotLimit.y);
	//velocity.y = 0.4 * -(rotation0.x / rotLimit.x);
	//position0.x += velocity.x;
	//position0.y += velocity.y;
	//position0.z += velocity.z;
}

void Player::Rotate(XMFLOAT3 targetPos)
{
	//Quaternion q;

	//targetPos = XMFLOAT3(10, 10000, 1);
	//q.RotateTowards(XMFLOAT4{0,0,0,0}, 10);
	//

	//rotation0.y = max(rotation0.y, -rotLimit.y);
	//rotation0.y = min(rotation0.y, +rotLimit.y);
	//rotation0.x = max(rotation0.x, -rotLimit.x);
	//rotation0.x = min(rotation0.x, +rotLimit.x);
}

void Player::ShotStraightBullet()
{

	//	const float bulletSpeed = 6;
	//

	//	std::unique_ptr<PlayerBullet> newBullet = std::make_unique<PlayerBullet>(); // Allocate memory for the new bullet
	//
	//	newBullet->Initialize();
	//

	//	bullets_.push_back(std::move(newBullet));

}

void Player::UpdateCollision()
{
	DirectX::XMFLOAT3 Min = {
		finalPos.x - scale0.x,
		finalPos.y - scale0.y,
		finalPos.z - scale0.z };
	DirectX::XMFLOAT3 Max = {
		finalPos.x + scale0.x,
		finalPos.y + scale0.y,
		finalPos.z + scale0.z };

	for (std::unique_ptr<Collision>& collision : collisionsObstacle)
	{

		if (-2 + finalPos.x <= Max.x - collision->GetMin().x && Max.x - collision->GetMin().x <= 2 + finalPos.x)
		{
			while (collision->Update(finalPos, scale0) == 1)
			{
				finalPos.x = 0.0002f;
			}
		}

		if (-2 + finalPos.x <= Min.x - collision->GetMax().x && Min.x - collision->GetMax().x <= 2 + finalPos.x)
		{
			while (collision->Update(finalPos, scale0) == 1)
			{
				finalPos.x += 0.0002f;
			}
		}

		if (-2 + finalPos.z <= Max.z - collision->GetMin().z && Max.z - collision->GetMin().z <= 2 + finalPos.z)
		{
			while (collision->Update(finalPos, scale0) == 1)
			{
				finalPos.z -= 0.0002f;

			}
		}

		if (-2 + finalPos.z <= Min.z - collision->GetMax().z && Min.z - collision->GetMax().z <= 2 + finalPos.z)
		{
			while (collision->Update(finalPos, scale0) == 1)
			{
				finalPos.z += 0.0002f;
			}
		}


	}
}

void Player::SetCollisionObstacle(DirectX::XMFLOAT3 position, DirectX::XMFLOAT3 scale)
{
	std::unique_ptr<Collision>newCollision = std::make_unique<Collision>();
	newCollision->SetObject(position, scale);
	collisionsObstacle.push_back(std::move(newCollision));
}

void Player::SetCollisionFloor(DirectX::XMFLOAT3 position, DirectX::XMFLOAT3 scale)
{
	std::unique_ptr<Collision>newCollision = std::make_unique<Collision>();
	newCollision->SetObject(position, scale);
	collisionsFloor.push_back(std::move(newCollision));
}

void Player::ClearCollision()
{
	collisionsObstacle.clear();
	collisionsFloor.clear();
}
void Player::PlayerRotate()
{
	float ap = MathFunc::easeInOutSine(6.3f - minFrame);
	if (rotateFlag == 0) {
		if (input->PushKey(DIK_P))
		{
			rotateFlag = 1;
		}
	}
	if (rotateFlag == 1) {
		distanceTimer++;

		if (distanceTimer <= 20) {
			frame -= 0.27f;
		}
		if (distanceTimer >= 20) {
			frame -= 0.02f;
		}
	}
	if (distanceTimer >= distanceTime)
	{
		distanceTimer = 0;
		rotateFlag = 0;
		frame = 0.0f;
	}
	if (input->PushKey(DIK_R)) {
		frame = 0;
		rotateFlag = 0;
	}
}

void Player::SetTitle()
{
	object0->SetPosition(finalPos);
	object0->SetScale({ scale0 });
	object0->SetRotation({ finalRotation });
}

void Player::SetTutorial()
{
	object0->SetPosition(finalPos);
	object0->SetScale({ scale0 });
	object0->SetRotation({ finalRotation });
}