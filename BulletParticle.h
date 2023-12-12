#pragma once
#include "Camera.h"
#include "Input.h"
#include "DXInput.h"
#include "FbxModel.h"
#include "FbxObject3D.h"
#include "DirectXCommon.h"

/**
 * @file BulletParticle.h
 * @brief Player Bullet Particles
 * @author Nauldee Nawill
 */

class BulletParticle
{
public:
	//functions
	BulletParticle() {};
	~BulletParticle() {};

	void Initialize(FbxModel* model, XMFLOAT3 parent);

	void Update();

	void Draw(ID3D12GraphicsCommandList* cmdList);


	static void SetDevice(ID3D12Device* device) { BulletParticle::device = device; }
	static void SetCamera(Camera* camera) { BulletParticle::camera = camera; }
	static void SetInput(Input* input) { BulletParticle::input = input; }
	static void SetDXInput(DXInput* dxInput) { BulletParticle::dxInput = dxInput; }
	void SetParent3d(XMFLOAT3* parent) { this->parent_ = parent; }
	//sets player translation
	void SetPosition0(DirectX::XMFLOAT3 pos) { position1 = pos; }
	void SetPosition1(DirectX::XMFLOAT3 pos) { position0 = pos; }
	void SetRotation0(DirectX::XMFLOAT3 rot) { rotation0 = rot; }
	void SetScale0(DirectX::XMFLOAT3 sca) { scale0 = sca; }
	bool SetDeath() { return isDead = true; }

	//gets player translations
	DirectX::XMFLOAT3 GetPosition0() { return position0; }
	DirectX::XMFLOAT3 GetPosition1() { return position1; }
	DirectX::XMFLOAT3 GetFinalPos() { return finalPos; }
	DirectX::XMFLOAT3 GetCameraPos0() { return cameraPos0; }
	DirectX::XMFLOAT3 GetCenterPos() { return centerpos; }
	DirectX::XMFLOAT3 GetRotation0() { return rotation0; }
	DirectX::XMFLOAT3 GetScale0() { return scale0; }
	bool GetDeath() { return isDead; }
private:
	//variables
	//device, input and camera
	static ID3D12Device* device;

	static Camera* camera;

	static Input* input;

	static DXInput* dxInput;
	//object translation related

	DirectX::XMFLOAT3 position0 = { 0.0f,0.5f,0.0f };
	DirectX::XMFLOAT3 position1 = { 0.0f,0.5f,0.0f };
	DirectX::XMFLOAT3 finalPos = { 0.0f,0.5f,0.0f };
	DirectX::XMFLOAT3 cameraPos0 = { 0.0f,0.5f,0.0f };
	DirectX::XMFLOAT3 centerpos = { 0.0f,0.5f,0.0f };
	DirectX::XMFLOAT3 rotation0 = { 0.0f,0.0f,0.0f };
	DirectX::XMFLOAT3 scale0 = { 0.02f,0.01f,0.01f };

	XMVECTOR posA = { 0.01f,0.01f,0.01f };
	XMVECTOR posB = { 0.01f,0.01f,0.01f };
	XMVECTOR posC = { 0.01f,0.01f,0.01f };
	XMVECTOR posD = { 0.01f,0.01f,0.01f };

	bool isRotZRight = true;

	float swayZ = 0.0f;
	bool isDead = false;
	static const XMFLOAT3 rotLimit;
	XMFLOAT3 rot = { 0, 0, 0 };

	const XMFLOAT3* parent_ = nullptr;
	DirectXCommon* dxCommon_ = nullptr;
public:

	//fbx
	FbxModel* model0 = nullptr;
	FbxObject3D* object0 = nullptr;

	FbxModel* model1 = nullptr;
	FbxObject3D* object1 = nullptr;
};