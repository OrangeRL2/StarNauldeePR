#pragma once
#include "Camera.h"
#include "FbxObject3D.h"
#include "WinApp.h"
#include "input.h"
#include "Spline.h"
#include "Player.h"

class RailCamera {
public:
	//�C���X�^���X
	RailCamera();
	~RailCamera();
	//������
	void Initialize();
	//�X�V
	void Update(Player* player_, std::vector<XMFLOAT3>& point);
	void ViewUpdate();

	void TitleR(Player* player_);

	void SetPlayer(Player* player_);
	void SetEye(XMFLOAT3 view);
	void SetTarget(XMFLOAT3 target_);
	void ShakeCamera();

	//�x�N�g����擾
	void GetVec(XMFLOAT3 a, XMFLOAT3 b);

	Camera* GetView() { return viewProjection; }
	bool GetIsEnd() { return isEnd; }

	FbxObject3D* GetCamera() { return camera; }
private:
	Input* input_ = nullptr;
	Camera* viewProjection = nullptr;
	FbxObject3D* camera = nullptr;
	Input* input = nullptr;
	//fever
	int feverTime;
	bool isFever = false;

	//�X�v���C��
	Spline spline_;
	Spline splineCam;

	XMFLOAT3 rightVec = { 0, 0, 0 };
	XMFLOAT3 leftVec = { 0, 0, 0 };
	XMFLOAT3 frontVec = { 0, 0, 0 };
	XMFLOAT3 oldCamera = { 0,0,0 };

	float timeRate;
	bool isEnd;
};

