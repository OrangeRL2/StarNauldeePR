#pragma once
#include "memory"
#include "list"

#include "Input.h"
#include "DXInput.h"
#include "DirectXCommon.h"
#include "FbxObject3D.h"
#include "Collision.h"
#include "Camera.h"
#include "Sprite.h"
#include"Player.h"
#include"PlayerBullet.h"
#include "Spline.h"
#include"JsonLoader.h"
#include"TitleManager.h"

class GameScene
{
	//Member Functions
public:
	GameScene();
	~GameScene();
	void Initialize(DirectXCommon* dxCommon, Input* input);
	//Update
	void Update();
	//Draw
	void Draw();
	//Title Scene
	void TitleUpdate();
	void TitleDraw();
	//Game Scene
	void GameUpdate();
	void GameDraw();

	//Scene Setters
	void SetTitle();
	void SetTutorial();
	void SetStage1();
	void SetStage2();
	void SetStage3();
	void SetStage4();
	void SetStage5();

	//CSV Editor
	void LoadCsv(const wchar_t* fileName, int obstacleVal);
	void DebugLoadCsv(const wchar_t* fileName, int obstacleVal);

	//Member Variables
private:
	//device and input
	DirectXCommon* dxCommon_ = nullptr;
	Input* input_ = nullptr;
	DXInput* dxInput = new DXInput();
	
	//Camera
	std::unique_ptr<Camera> camera_;

	//------------Model Related-------------
	//fbx
	FbxModel* model1 = nullptr;
	FbxModel* model2 = nullptr;
	//岩のモデル
	FbxModel* stoneModel = nullptr;
	//ゴールのモデル
	FbxModel* goalModel = nullptr;
	//鍵のモデル
	FbxModel* keyModel = nullptr;
	
	//Stage and Title models
	//title
	FbxModel* titleModel = nullptr;
	//stage1
	FbxModel* stage1Model = nullptr;
	//stage2
	FbxModel* stage2Model = nullptr;
	//stage3
	FbxModel* stage3Model = nullptr;
	//stage4
	FbxModel* stage4Model = nullptr;
	//stage5
	FbxModel* stage5Model = nullptr;
	//tutorial
	FbxModel* stageTutoModel = nullptr;
	//clear1
	FbxModel* clear1Model = nullptr;
	//instruction
	FbxModel* moveTextModel = nullptr;
	FbxModel* startTextModel = nullptr;
	FbxModel* jumpTextModel = nullptr;
	FbxModel* cameraTextModel = nullptr;
	FbxModel* zoomTextModel = nullptr;
	FbxModel* returnTextModel = nullptr;

	//----------My Classes---------
	//Title manager
	std::unique_ptr<TitleManager> title;
	//Player
	std::unique_ptr<Player> player;
	std::unique_ptr<PlayerBullet> playerBullet;

	//Level Editor
	JsonLoader* jsonLoader = nullptr;
	//
	std::list<std::unique_ptr<FbxObject3D>> objects;

	std::list<std::unique_ptr<FbxModel>> models;
	DirectX::XMFLOAT3 position{ 0,0,0 };
	float ap;

	//RailCamera
	XMFLOAT3 start;
	XMFLOAT3 p2;
	XMFLOAT3 p3;
	XMFLOAT3 p4;
	XMFLOAT3 end;

	//								p0	p1	p2	p3	p4	p5
	std::vector<XMFLOAT3> points{ start,start,p2,p3,p4,end,end };
	
	float timeRate;

	Spline spline_;
	XMFLOAT3 cameraPosition;
	XMFLOAT3 eye_;

	//---------------------------

	//sprite
	Sprite* sprite = new Sprite;
	Sprite titleSprite;	//title.png
	Sprite keySprite;	//key.png
	//sprite common generation
	SpriteCommon spriteCommon;

	//scene
	enum class Scene
	{
		Title,	//title
		Game,	//game
	};
	//sets first scene to title
	size_t scene_ = static_cast<size_t>(Scene::Title);
	//previous scene
	size_t preScene_ = static_cast<size_t>(Scene::Title);
	//Pointer Table
	static void (GameScene::* Scene_[])();

	//Scene Draw
	enum class SceneDraw
	{
		TitleDraw,	//タイトル
		GameDraw,	//ゲーム
	};
	//sets first scene to titledraw
	size_t sceneDraw_ = static_cast<size_t>(SceneDraw::TitleDraw);
	//table
	static void (GameScene::* SceneDraw_[])();

	//stage separation
	enum Stage
	{
		Title,
		Tutorial,
		Stage1,
		Stage2,
		Stage3,
		Stage4,
		Stage5,
	};
	//stage
	Stage stage = Stage::Title;
	//previous stage
	Stage preStage = Stage::Title;

	//amount of obstacles pre stage
	//tutorial
	size_t tutorialObstacleVal = 9;
	size_t tutorialObstacleVal1 = 9;
	size_t tutorialObstacleVal2 = 21;
	size_t tutorialObstacleVal3 = 24;
	size_t tutorialObstacleVal4 = 126;
	size_t tutorialObstacleVal5 = 126;
	size_t stage1ObstacleVal = 5;

	float num = 0;

	//clear flags
	bool clearTutoFlag = false;
	bool clear1Flag = false;
	bool clear2Flag = false;
	bool clear3Flag = false;
	bool clear4Flag = false;
	bool clear5Flag = false;
	bool clear6Flag = false;
};