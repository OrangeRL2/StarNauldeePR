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
	scale0 = { 0.01f,0.01f,0.01f };
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
	if (isDead == false) {
		object0->Draw(cmdList);
	}
}


void Player::PlayerMove()
{
	//player movement
	if (input->PushKey(DIK_W))
	{

		position0.y += velocity0.y;
		centerpos.y += 0.4f;
		rotation0.z -= 0.05f;

	}
	if (input->PushKey(DIK_S))
	{
		if (position0.y >= -21.0f) {
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

void Player::ShotStraightBullet()
{
	//bullet
	//	const float bulletSpeed = 6;
	//

	//	std::unique_ptr<PlayerBullet> newBullet = std::make_unique<PlayerBullet>(); // Allocate memory for the new bullet
	//
	//	newBullet->Initialize();
	//

	//	bullets_.push_back(std::move(newBullet));

}

void Player::PlayerRotate()
{
	//player barrel roll

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
	object0->SetPosition(position0);
	object0->SetScale({ scale0 });
	object0->SetRotation({ finalRotation });
}

void Player::SetTutorial()
{
	object0->SetPosition(finalPos);
	object0->SetScale({ scale0 });
	object0->SetRotation({ finalRotation });
	scale0 = { 0.01f,0.01f,0.01f };
}

void Player::TitleUpdate()
{
	//title screen movement
	static int time[4] = { 150,100,50,0 };
	static int timespd[4] = { 1,1,1,1 };
	for (int i = 0; i < 4; i++)
	{
		time[i] += timespd[i];
		if (time[i] >= 360 || time[i] <= 0)
		{
			timespd[i] = -timespd[i];
		}
	}

	position0.x -= 0.5f;
	if (position0.x < -100.0f) {
		position0.x = 100.0f;
	}
	scale0 = { 0.05f,0.05f,0.05f };
	//position0.z = -50.0f;
	object0->SetPosition(position0);
	finalRotation = XMFLOAT3{ frame + rotation0.x,
								0 + rotation0.y ,
								0 + rotation0.z };

	object0->SetScale({ scale0 });
	object0->SetRotation({ finalRotation });
	PlayerMove();
	PlayerRotate();
	//if (rotateFlag == 0) {
	//	if (input->PushKey(DIK_W))
	//	{
	//		rotateFlag = 1;
	//	}
	//}
	object0->Update();
	/*position0.y += cosf(MathFunc::DegreeConversionRad(time[0])*0.1);*/
	//position0.z=
}

void Player::revive()
{
	isDead = false;
	finalPos = { 0.0f,0.5f,0.0f };
}