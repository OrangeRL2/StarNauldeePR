#pragma once
#include "Camera.h"
#include "Input.h"
#include "DXInput.h"
#include "FbxModel.h"
#include "FbxObject3D.h"
#include "DirectXCommon.h"
class PlayerBullet
{
public:
	//�R���X�g���N�^
	PlayerBullet() {};
	//�f�X�g���N�^
	~PlayerBullet() {};
	//������
	void Initialize(FbxModel* model, XMFLOAT3 parent);
	//�X�V
	void Update();
	//�`��
	void Draw(ID3D12GraphicsCommandList* cmdList);

	void PlayerMove();

	void CameraFollow();
	void BulletShot();
	void Rotate(XMFLOAT3 targetPos);
	float Deg2Rad(float targetPos);

	//�ÓI�����o�֐�
	static void SetDevice(ID3D12Device* device) { PlayerBullet::device = device; }
	static void SetCamera(Camera* camera) { PlayerBullet::camera = camera; }
	static void SetInput(Input* input) { PlayerBullet::input = input; }
	static void SetDXInput(DXInput* dxInput) { PlayerBullet::dxInput = dxInput; }
	void SetParent3d(XMFLOAT3* parent) { this->parent_ = parent; }
	//�Z�b�^�[
	//�ό`�s��Z�b�g
	void SetPosition0(DirectX::XMFLOAT3 pos) { position1 = pos; }
	void SetPosition1(DirectX::XMFLOAT3 pos) { position0 = pos; }
	void SetRotation0(DirectX::XMFLOAT3 rot) { rotation0 = rot; }
	void SetScale0(DirectX::XMFLOAT3 sca) { scale0 = sca; }
	//�Q�b�^�[
	//�ό`�s��
	DirectX::XMFLOAT3 GetPosition0() { return position0; }
	DirectX::XMFLOAT3 GetPosition1() { return position1; }
	DirectX::XMFLOAT3 GetFinalPos() { return finalPos; }
	DirectX::XMFLOAT3 GetCameraPos0() { return cameraPos0; }
	DirectX::XMFLOAT3 GetCenterPos() { return centerpos; }
	DirectX::XMFLOAT3 GetRotation0() { return rotation0; }
	DirectX::XMFLOAT3 GetScale0() { return scale0; }
private:
	//�f�o�C�X
	static ID3D12Device* device;
	//�J����
	static Camera* camera;
	//�L�[�{�[�h
	static Input* input;
	//�R���g���[���[
	static DXInput* dxInput;



	//�ό`�s��
	DirectX::XMFLOAT3 position0 = { 0.0f,0.5f,0.0f };
	DirectX::XMFLOAT3 position1 = { 0.0f,0.5f,0.0f };
	DirectX::XMFLOAT3 finalPos = { 0.0f,0.5f,0.0f };
	DirectX::XMFLOAT3 cameraPos0 = { 0.0f,0.5f,0.0f };
	DirectX::XMFLOAT3 centerpos = { 0.0f,0.5f,0.0f };
	DirectX::XMFLOAT3 rotation0 = { 0.0f,0.0f,0.0f };
	DirectX::XMFLOAT3 scale0 = { 0.01f,0.01f,0.01f };

	//z��������]���E��]��
	bool isRotZRight = true;
	//z��������]�p
	float swayZ = 0.0f;
	//���@�̉�]���E
	static const XMFLOAT3 rotLimit;
	XMFLOAT3 rot = { 0, 0, 0 };
	// �e�ƂȂ郏�[���h�ϊ��ւ̃|�C���^
	const XMFLOAT3* parent_ = nullptr;
	DirectXCommon* dxCommon_ = nullptr;
public:

	//fbx
	FbxModel* model0 = nullptr;
	FbxObject3D* object0 = nullptr;

	FbxModel* model1 = nullptr;
	FbxObject3D* object1 = nullptr;
};