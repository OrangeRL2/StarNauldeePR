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
	void FrontDraw();
	//void ThanksForPlayingText();
	void ModelDraw();

	bool IsTitle() { return isTitle; };

	//void NotTitle() { isTitle = false; };
	void TitleBack() { isTitle = true; };

	bool isTitle = true;

	bool endflag = false;

private:
	static ID3D12Device* device;

	static Camera* camera;

	static Input* input;

	static DXInput* dxInput;
private:
	
	//スプライト
	Sprite* sprite = new Sprite;
	Sprite titleSprite;	//title.png
	Sprite pressSpace;	//start.png
	Sprite nintendoCopyright;//start.png

	//スプライト共通データ生成
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
	float turnSpeed = 0.0;
	float speed = 0.4;
	float turning = 0;
	float posY[3] = { 0,0,0 };
};

