#pragma once
#include "Camera.h"
#include "Input.h"
#include "DXInput.h"
#include "FbxModel.h"
#include "FbxObject3D.h"
#include "PlayerBullet.h"
#include "List"
#include "Collision.h"
#include "Mathfunc.h"
#include "Vector3.h"

/**
 * @file Player.h
 * @brief Class for Player
 * @author Nauldee Nawill
 */

class Player
{
public:
	//Constructor ETC
	Player() {};
	~Player() {};

	void Initialize(FbxModel* model, FbxModel* bulletModel);
	void Update(XMFLOAT3 spline);
	void Draw(ID3D12GraphicsCommandList* cmdList);

	//Player Movement Functions
	void PlayerMove();
	void TitleUpdate();
	void CameraFollow();
	void Rotate(XMFLOAT3 targetPos);
	void PlayerRotate();

	//Bullet
	void ShotStraightBullet();
	float Deg2Rad(float targetPos);

	//Setters
	static void SetDevice(ID3D12Device* device) { Player::device = device; }
	static void SetCamera(Camera* camera) { Player::camera = camera; }
	static void SetInput(Input* input) { Player::input = input; }
	static void SetDXInput(DXInput* dxInput) { Player::dxInput = dxInput; }

	void SetParent3d(XMFLOAT3* parent) { this->parent_ = parent; }
	void SetPosition0(DirectX::XMFLOAT3 pos) { position1 = pos; }
	void SetPosition1(DirectX::XMFLOAT3 pos) { position0 = pos; }
	void SetRotation0(DirectX::XMFLOAT3 rot) { rotation0 = rot; }
	void SetScale0(DirectX::XMFLOAT3 sca) { scale0 = sca; }

	void SetTitle();
	void SetTutorial();
	void SetStage();
	void SetStage2();
	void SetStage4();
	//Getters
	DirectX::XMFLOAT3 GetPosition0() { return position0; }
	DirectX::XMFLOAT3 GetPosition1() { return position1; }
	DirectX::XMFLOAT3 GetFinalPos() { return finalPos; }
	DirectX::XMFLOAT3 GetFinalPos1() { return finalPos1; }
	DirectX::XMFLOAT3 GetCameraPos0() { return cameraPos0; }
	DirectX::XMFLOAT3 GetCenterPos() { return centerpos; }
	DirectX::XMFLOAT3 GetRotation0() { return rotation0; }
	DirectX::XMFLOAT3 GetScale0() { return scale0; }
	DirectX::XMFLOAT3 GetBulletPos() { return bulletPos2; }
	bool GetIsDead() { return isDead; }
	bool IsDead() { return isDead = true; }
	void revive();

private:
	//statics
	static ID3D12Device* device;

	static Camera* camera;

	static Input* input;

	static DXInput* dxInput;

	//fbx
	FbxModel* model0 = nullptr;
	FbxObject3D* object0 = nullptr;

	FbxModel* model1 = nullptr;
	FbxObject3D* object1 = nullptr;

	PlayerBullet* playerBullet;
	//movement
	DirectX::XMFLOAT3 position0 = { 0.0f,0.5f,0.0f };
	DirectX::XMFLOAT3 position1 = { 0.0f,0.5f,0.0f };

	DirectX::XMFLOAT3 velocity0 = { 0.2f,0.2f,0.2f };
	DirectX::XMFLOAT3 velocity1 = { 0.2f,0.2f,0.2f };
	DirectX::XMFLOAT3 finalPos = { 0.0f,0.5f,0.0f };
	DirectX::XMFLOAT3 finalPos1 = { 0.0f,0.5f,0.0f };
	DirectX::XMFLOAT3 cameraPos0 = { 0.0f,0.5f,0.0f };
	DirectX::XMFLOAT3 centerpos = { 0.0f,0.5f,0.0f };
	DirectX::XMFLOAT3 rotation0 = { 0.0f,0.0f,0.0f };
	DirectX::XMFLOAT3 finalRotation = { 0.0f,0.0f,0.0f };
	DirectX::XMFLOAT3 scale0 = { 0.01f,0.01f,0.01f };

	const float verticalLimit = 21.0f;
	const float horizontalLimit = 20.0f;
	const float xRotationChange = 0.1f;
	const float zRotationChange = 0.05f;

	bool isRotZRight = true;
	float swayZ = 0.0f;
	static const XMFLOAT3 rotLimit;
	XMFLOAT3 rot = { 0, 0, 0 };
	const XMFLOAT3* parent_ = nullptr;

	float rotation = 120;
	//easing
	float minFrame = 0.0f;
	float frame = 0.0f;
	float maxFrame = 6.20f;
	int rotateFlag;

	float distanceTime = 60.0f;

	float distanceTimer = 0.0f;

	bool isDead = false;

	//player speed
	float speed = 0.5f;

	//bullet related
	DirectX::XMFLOAT3 bulletPos = { finalPos.x,finalPos.y,finalPos.z };
	DirectX::XMFLOAT3 bulletPos2 = { finalPos.x,finalPos.y,finalPos.z };

	std::list<std::unique_ptr<PlayerBullet>> objects;
	bool isBulletDead = false;

	//reticle related
	FbxModel* retModel = nullptr;
	FbxObject3D* retObject = nullptr;

	DirectX::XMFLOAT3 retPos = { -20.0f,0.5f,0.0f };
	DirectX::XMFLOAT3 retFinalPos = { 0.0f,0.5f,0.0f };
};