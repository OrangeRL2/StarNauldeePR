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
#include "SpritePop.h"

/**
 * @file TitleManager.h
 * @brief Class for setting up title screen
 * @author Nauldee Nawill
 */

enum TitleMenu
{
	start,
	end,
};

class TitleManager
{
public:
	void Initialize(FbxModel* model, FbxModel* model2, ID3D12Device* dev);

	
	//Title
	void Update(FbxModel* model, FbxModel* model2, ID3D12Device* dev);
	void Draw(ID3D12GraphicsCommandList* cmdList_,ID3D12Device* dev);
	//Game
	void GameDraw(ID3D12GraphicsCommandList* cmdList_, ID3D12Device* dev);
	void ModelDraw(ID3D12Device* dev);
	void Transition(ID3D12Device* dev);
	void PopInit(ID3D12Device* dev);
	void PopTransInit(ID3D12Device* dev);
	void TransitionPop(ID3D12Device* dev);
	void TransitionReset();
	void OverDraw(ID3D12GraphicsCommandList* cmdList_, ID3D12Device* dev);
	//Setters
	void SetPosition(DirectX::XMFLOAT3 pos) { position = pos; }
	void SetRotation(DirectX::XMFLOAT3 rot) { rotation = rot; }
	void SetScale(DirectX::XMFLOAT3 sca) { scale = sca; }
	static void SetDevice(ID3D12Device* device) { TitleManager::device = device; }
	static void SetCamera(Camera* camera) { TitleManager::camera = camera; }
	static void SetInput(Input* input) { TitleManager::input = input; }
	static void SetDXInput(DXInput* dxInput) { TitleManager::dxInput = dxInput; }
	
private:
	static ID3D12Device* device;

	static Camera* camera;

	static Input* input;

	static DXInput* dxInput;
private:
	//Sprite
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
	Sprite controlImage;//Controls.png

	Sprite starSprite;//star.png
	Sprite arwingSprite;//arwing.png

	Sprite start;//START.png
	Sprite level1;//LEVEL1.png

	Sprite GAMEOVER;//GAMEOVER.png

	SpriteCommon spriteCommon;

	//fbx
	FbxModel* arwingModel = nullptr;
	FbxObject3D* arwingObject = nullptr;

	FbxModel* foxModel = nullptr;
	FbxObject3D* foxObject = nullptr;

	FbxModel* frogModel = nullptr;
	FbxObject3D* frogObject = nullptr;

	//Variables
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

	DirectX::XMFLOAT3 position = { 0.0f,0.0f,0.0f };
	DirectX::XMFLOAT3 position0 = { 0.0f,0.0f,0.0f };
	DirectX::XMFLOAT3 position1 = { 0.0f,0.0f,0.0f };
	DirectX::XMFLOAT3 rotation = { 0.0f,0.5f,0.0f };
	DirectX::XMFLOAT3 scale = { 0.0f,0.5f,0.0f };
	DirectX::XMFLOAT3 startPos = { 200.0f,-2600.0f+400.0f,0.0f };
	DirectX::XMFLOAT3 levelPos = { 200.0f,-2000.0f+400.0f,0.0f };

	enum class Phase2 {
		Approach,//Approaches
		Leave,//Leaves
	};
	//フェーズ
	Phase2 phase2_ = Phase2::Approach;
	int maxEnemyCount = 0;
	bool isDead = false;
	DirectX::XMFLOAT3 popPos = { 1000.0f,0.0f,0.0f };
	float popRot = 0.0f;
	int eventSlayCount = 0;

	std::list<std::unique_ptr<SpritePop>> poppy;
	std::list<std::unique_ptr<SpritePop>> transPop;

	bool isTitle = true;
	bool endflag = false;
	bool gameStartFlag = false;
public:
	float GetTurning() { return turning; };
	void TitleBack() { isTitle = true; };
	bool IsTitle() { return isTitle; };
	bool IsDead() { return isDead; }
	bool GetStartFlag() { return gameStartFlag; }
};

