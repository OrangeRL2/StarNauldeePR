#pragma once
#include "Input.h"
#include "Sprite.h"
#include "Camera.h"
#include "DXInput.h"
#include "FbxModel.h"
#include "FbxObject3D.h"
#include "List"
#include "Mathfunc.h"
#include "SimpleMath.h"
#include "MathFunc.h"
enum TitleMenu
{
	start,
	end,
};

class TitleManager
{
public:
	void Initialize(FbxModel* model, FbxModel* model2, ID3D12Device* dev);
	void Update();
	void Draw(ID3D12GraphicsCommandList* cmdList_,ID3D12Device* dev);

	void End();

	void BackDraw();
	void TitleFrontDraw();
	void WinDraw();
	void StartDraw();
	void GameDraw(ID3D12GraphicsCommandList* cmdList_, ID3D12Device* dev);
	//void ThanksForPlayingText();
	void ModelDraw();

	void Transition();

	bool IsTitle() { return isTitle; };

	void SetPosition(DirectX::XMFLOAT3 pos) { position = pos; }
	void SetRotation(DirectX::XMFLOAT3 rot) { rotation = rot; }
	void SetScale(DirectX::XMFLOAT3 sca) { scale = sca; }

	//void NotTitle() { isTitle = false; };
	void TitleBack() { isTitle = true; };

	static void SetDevice(ID3D12Device* device) { TitleManager::device = device; }
	static void SetCamera(Camera* camera) { TitleManager::camera = camera; }
	static void SetInput(Input* input) { TitleManager::input = input; }
	static void SetDXInput(DXInput* dxInput) { TitleManager::dxInput = dxInput; }

	bool isTitle = true;

	bool endflag = false;

private:
	static ID3D12Device* device;

	static Camera* camera;

	static Input* input;

	static DXInput* dxInput;
private:
	
	Sprite* sprite = new Sprite;
	Sprite titleSprite;	//title.png
	Sprite titleSprite2;	//title.png
	Sprite pressSpace;	//start.png
	Sprite nintendoCopyright;//start.png

	Sprite S;//S.png
	Sprite T;//T.png
	Sprite A;//A.png
	Sprite R;//R.png
	Sprite T2;//T2.png

	Sprite handle;//handle2.png
	Sprite titleImage;//titleImage.png

	SpriteCommon spriteCommon;

	//fbx
	FbxModel* arwingModel = nullptr;
	FbxObject3D* arwingObject = nullptr;

	FbxModel* foxModel = nullptr;
	FbxObject3D* foxObject = nullptr;

	FbxModel* frogModel = nullptr;
	FbxObject3D* frogObject = nullptr;

	float oldHori = 0;
	float horizontalRotation = 0;

	float oldVer = 0;
	float verticalRotation = 0;

	int titleMenu = TitleMenu::start;

	int mouseAnimeNum = 0;
	int mouseAnimeTime = 0;
	float turnSpeed = 0.0f;
	float speed = 0.4f;
	float turning = 0.0f;
	float posY[3] = { 0.0f,0.0f,0.0f };

	DirectX::XMFLOAT3 position = { 0.0f,0.5f,0.0f };
	DirectX::XMFLOAT3 position0 = { 0.0f,0.5f,0.0f };
	DirectX::XMFLOAT3 position1 = { 0.0f,0.5f,0.0f };
	DirectX::XMFLOAT3 rotation = { 0.0f,0.5f,0.0f };
	DirectX::XMFLOAT3 scale = { 0.0f,0.5f,0.0f };

	enum class Phase2 {
		Approach,//接近する
		Leave,//離脱する
	};
	//フェーズ
	Phase2 phase2_ = Phase2::Approach;

public:
	float GetTurning() { return turning; };
};

