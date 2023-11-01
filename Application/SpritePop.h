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
class SpritePop
{
public:
	//initializes sprite for scene transition
	void PopTransInit(ID3D12Device* dev);
	//initializes sprite
	void PopInit(ID3D12Device* dev);
	//updates sprite
	void PopUpdate();
	//updates transition
	void PopTransition();
	//draws
	void PopDraw(ID3D12GraphicsCommandList* cmdList_, ID3D12Device* dev);
	//deletes sprite
	void PopCollision();
	//getter
	bool IsDead() { return isDead; }
	//revives
	void revival() { isDead = false; };
	//destroys
	void dead() { isDead = true; };
private:
	static ID3D12Device* device;

	static Camera* camera;

	static Input* input;

	static DXInput* dxInput;


private:
	Sprite* sprite = new Sprite;
	SpriteCommon spriteCommon;
	Sprite star;//star.png

	bool isDead = false;

	DirectX::XMFLOAT3 position = { 500.0f,0.5f,0.0f };
	DirectX::XMFLOAT2 scale = { 0.0f,0.0f};
	float rotation = 0.0f;
};

