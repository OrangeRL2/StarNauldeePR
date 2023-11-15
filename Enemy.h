//#pragma once
//#include "Camera.h"
//#include "Input.h"
//#include "DXInput.h"
//#include "FbxModel.h"
//#include "FbxObject3D.h"
//#include "PlayerBullet.h"
//#include "List"
//#include "Collision.h"
//
//class Enemy
//{
//public:
//	//�R���X�g���N�^
//	Enemy() {};
//	//�f�X�g���N�^
//	~Enemy() {};
//	//������
//	void Initialize(FbxModel* model, FbxModel* model2);
//	//�X�V
//	void Update(XMFLOAT3 spline);
//	//�`��
//	void Draw(ID3D12GraphicsCommandList* cmdList);
//
//	void EnemyMove();
//
//	void CameraFollow();
//
//	/// <summary>
//	/// shoots bullet
//	/// </summary>
//	void ShotStraightBullet();
//
//	void Rotate(XMFLOAT3 targetPos);
//	float Deg2Rad(float targetPos);
//
//	//setters
//	static void SetDevice(ID3D12Device* device) { Enemy::device = device; }
//	static void SetCamera(Camera* camera) { Enemy::camera = camera; }
//	static void SetInput(Input* input) { Enemy::input = input; }
//	static void SetDXInput(DXInput* dxInput) { Enemy::dxInput = dxInput; }
//	void SetParent3d(XMFLOAT3* parent) { this->parent_ = parent; }
//
//	//setters
//	void SetPosition0(DirectX::XMFLOAT3 pos) { position1 = pos; }
//	void SetPosition1(DirectX::XMFLOAT3 pos) { position0 = pos; }
//	void SetRotation0(DirectX::XMFLOAT3 rot) { rotation0 = rot; }
//	void SetScale0(DirectX::XMFLOAT3 sca) { scale0 = sca; }
//
//	//getters
//	DirectX::XMFLOAT3 GetPosition0() { return position0; }
//	DirectX::XMFLOAT3 GetPosition1() { return position1; }
//	DirectX::XMFLOAT3 GetFinalPos() { return finalPos; }
//	DirectX::XMFLOAT3 GetCameraPos0() { return cameraPos0; }
//	DirectX::XMFLOAT3 GetCenterPos() { return centerpos; }
//	DirectX::XMFLOAT3 GetRotation0() { return rotation0; }
//	DirectX::XMFLOAT3 GetScale0() { return scale0; }
//
//private:
//	//device
//	static ID3D12Device* device;
//	//camera
//	static Camera* camera;
//	//keyboard input
//	static Input* input;
//	//controller input
//	static DXInput* dxInput;
//
//	//fbx
//	FbxModel* model0 = nullptr;
//	FbxObject3D* object0 = nullptr;
//
//	FbxModel* model1 = nullptr;
//	FbxObject3D* object1 = nullptr;
//
//	DirectX::XMFLOAT3 position0 = { 0.0f,0.5f,0.0f };
//	DirectX::XMFLOAT3 velocity0 = { 0.8f,0.8f,0.8f };
//	DirectX::XMFLOAT3 position1 = { 0.0f,0.5f,0.0f };
//	DirectX::XMFLOAT3 finalPos = { 0.0f,0.5f,0.0f };
//	DirectX::XMFLOAT3 cameraPos0 = { 0.0f,0.5f,0.0f };
//	DirectX::XMFLOAT3 centerpos = { 0.0f,0.5f,0.0f };
//	DirectX::XMFLOAT3 rotation0 = { 0.0f,0.0f,0.0f };
//	DirectX::XMFLOAT3 scale0 = { 0.02f,0.02f,0.02f };
//
//	bool isRotZRight = true;
//	//z��������]�p
//	float swayZ = 0.0f;
//	//���@�̉�]���E
//	static const XMFLOAT3 rotLimit;
//	XMFLOAT3 rot = { 0, 0, 0 };
//	// �e�ƂȂ郏�[���h�ϊ��ւ̃|�C���^
//	const XMFLOAT3* parent_ = nullptr;
//	std::list<std::unique_ptr<PlayerBullet>>bullets_;
//	std::list<std::unique_ptr<FbxObject3D>> objects;
//	XMFLOAT3 bulletPos = { finalPos.x,finalPos.y,finalPos.z };
//
//	bool shotFlag = false;
//	int shotTimer = 0;
//};