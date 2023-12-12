#include "Player.h"
#include <SimpleMath.h>
ID3D12Device* Player::device = nullptr;
Camera* Player::camera = nullptr;
Input* Player::input = nullptr;
DXInput* Player::dxInput = nullptr;
const XMFLOAT3 Player::rotLimit = { 0.5f, 0.5f, 0.5f };
void Player::Initialize(FbxModel* model, FbxModel* bulletModel)
{
	model1 = bulletModel;

	object0 = new FbxObject3D;
	object0->Initialize();
	object0->SetModel(model);

	object1 = new FbxObject3D;
	object1->Initialize();
	object1->SetModel(model1);

	retObject = new FbxObject3D;
	retObject->Initialize();
	retObject->SetModel(model1);

	object0->SetScale({ scale0 });
	object1->SetScale({ scale0 });
	retObject->SetScale({ scale0 });
}
void Player::Update(XMFLOAT3 spline)
{
	objects.remove_if([](std::unique_ptr<PlayerBullet>& object0) {
		return object0->GetDeath();
		});

	PlayerRotate();
	PlayerMove();
	
	finalPos = XMFLOAT3{ spline.x + position0.x,
						 spline.y + position0.y ,
						 spline.z + position0.z };

	finalPos1 = XMFLOAT3{spline.x + position1.x,
						 spline.y + position1.y ,
						 spline.z + position1.z };

	retFinalPos = XMFLOAT3{ spline.x + retPos.x,
							spline.y + retPos.y ,
							spline.z + retPos.z };

	finalRotation = XMFLOAT3{ frame + rotation0.x,
								0 + rotation0.y ,
								0 + rotation0.z };
	object0->SetPosition(finalPos);
	object0->SetRotation({ finalRotation });

	object1->SetPosition(finalPos1);
	object1->SetRotation({ finalRotation });

	retObject->SetPosition(retFinalPos);

	object0->Update();
	object1->Update();
	retObject->Update();

	if (input->TriggerKey(DIK_SPACE))
	{
		ShotStraightBullet();
	}

	for (std::unique_ptr<PlayerBullet>& object0 : objects)
	{
		object0->Update(retFinalPos);
		bulletPos2 = object0->GetFinalPos();
	}

	float distanceThreshold = 1.0f; // You can adjust this threshold as needed
	//player1 follows player0
	XMVECTOR player0 = XMLoadFloat3(&position0);
	XMVECTOR player1 = XMLoadFloat3(&position1);
	float distance = XMVectorGetX(XMVector3Length(player0 - player1));

	// Check if the distance is greater than the threshold
	if (distance > distanceThreshold) {
	XMVECTOR direction = XMVector3Normalize(player0 - player1);
	player1 = player1 + direction / 6;
	XMStoreFloat3(&position1, player1);
	}
}

void Player::Draw(ID3D12GraphicsCommandList* cmdList)
{
	if (isDead == false) {
		object0->Draw(cmdList);
		retObject->Draw(cmdList);
		//object1->Draw(cmdList);
	}
	for (std::unique_ptr<PlayerBullet>& object0 : objects)
	{
		object0->Draw(cmdList);
	}
}


void Player::PlayerMove()
{
	speed = 0.2f;
	
	XMFLOAT3 move = GetPosition0();
	float obliques = 1.414213562f;

	//If there is simultaneous input, it will be corrected to 45 degrees.
	if (input->PushKey(DIK_W) || input->PushKey(DIK_S))
	{
		if (input->PushKey(DIK_A) || input->PushKey(DIK_D))
		{
			speed = speed / obliques;
		}
	}
	//player movement
	if (input->PushKey(DIK_W) && position0.y <= verticalLimit)
	{
			position0.y += speed;
			rotation0.z -= verticalRotSpeed;
	}
	if (input->PushKey(DIK_S) && position0.y >= -verticalLimit)
	{
			position0.y -= speed;
			rotation0.z += verticalRotSpeed;

	}
	if (input->PushKey(DIK_D) && position0.z <= horizontalLimit)
	{
			position0.z += speed;
			rotation0.x += horizontalRotSpeed;
	}
	if (input->PushKey(DIK_A) && position0.z >= -horizontalLimit)
	{
			position0.z -= speed;
			rotation0.x -= horizontalRotSpeed;
	}

	if (rotation0.z >= -standardRot) {
		rotation0.z -= rotSpeed;
	}
	else if (rotation0.z <= verticalRotLimit) {
		rotation0.z += rotSpeed;
	}
	if (rotation0.x <= standardRot) {
		rotation0.x += rotSpeed;
	}
	else if (rotation0.x >= standardRot) {
		rotation0.x -= rotSpeed;
	}

	//Limits player rotation
	rotation0.y = max(rotation0.y, -rotLimit.y);
	rotation0.y = min(rotation0.y, +rotLimit.y);
	rotation0.x = max(rotation0.x, -rotLimit.x);
	rotation0.x = min(rotation0.x, +rotLimit.x);
	rotation0.z = max(rotation0.z, -rotLimit.z);
	rotation0.z = min(rotation0.z, +rotLimit.z);

	//Moves player reticle
	if (input->PushKey(DIK_UP))
	{
			retPos.y += speed;
	}
	if (input->PushKey(DIK_DOWN))
	{
			retPos.y -= speed;
	}
	if (input->PushKey(DIK_RIGHT))
	{
			retPos.z += speed;
	}
	if (input->PushKey(DIK_LEFT))
	{
			retPos.z -= speed;
	}
}

void Player::ShotStraightBullet()
{
	//Initializes Player Bullet
	std::unique_ptr<PlayerBullet>newBullet = std::make_unique<PlayerBullet>();

	bulletPos = { finalPos.x-1.0f,finalPos.y,finalPos.z };

	newBullet->Initialize(model1, bulletPos, retFinalPos);

	objects.push_back(std::move(newBullet));

}

void Player::PlayerRotate()
{
	
	//Player Barrel Roll
	const float finalFrame = 20.0f;
	const float fastFrame = 0.27f;
	const float slowFrame = 0.02f;
	float ap = MathFunc::easeInOutSine(6.3f - minFrame);
	if (rotateFlag == false) {
		if (input->PushKey(DIK_P))
		{
			rotateFlag = true;
		}
	}
	if (rotateFlag == true) {
		distanceTimer++;

		if (distanceTimer <= finalFrame) {
			frame -= fastFrame;
		}
		if (distanceTimer >= finalFrame) {
			frame -= slowFrame;
		}
	}
	if (distanceTimer >= distanceTime)
	{
		distanceTimer = 0;
		rotateFlag = false;
		frame = 0.0f;
	}
	if (input->PushKey(DIK_R)) {
		frame = 0;
		rotateFlag = false;
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
	position0 = { 0.0f,0.5f,0.0f };
	scale0 = { 0.01f,0.01f,0.01f };
	object0->SetPosition(finalPos);
	object0->SetScale({ scale0 });
	object0->SetRotation({ finalRotation });
	
	position1 = finalPos;

	retPos = { -20.0f,0.5f,0.0f };
	retObject->SetPosition(retFinalPos);
}

void Player::TitleUpdate()
{
	//Title screen movement
	static int time[4] = { 150,100,50,0 };
	static int timespd[4] = { 1,1,1,1 };
	static int finalTime = 360;
	for (int i = 0; i < 4; i++)
	{
		time[i] += timespd[i];
		if (time[i] >= finalTime || time[i] <= 0)
		{
			timespd[i] = -timespd[i];
		}
	}

	//position0.x -= speed;
	//if (position0.x < -100.0f) {
	//	position0.x = 100.0f;
	//}
	scale0 = { 0.05f,0.05f,0.05f };

	object0->SetPosition(position0);
	finalRotation = XMFLOAT3{ frame + rotation0.x,
								0 + rotation0.y ,
								0 + rotation0.z };

	object0->SetScale({ scale0 });
	object0->SetRotation({ finalRotation });
	PlayerMove();
	PlayerRotate();

	object0->Update();

}

void Player::revive()
{
	isDead = false;
	finalPos = { 0.0f,0.5f,0.0f };
	position1 = { 0.0f,0.5f,0.0f };
}

