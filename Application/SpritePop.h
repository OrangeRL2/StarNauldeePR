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
	void PopTransInit(ID3D12Device* dev);
	void PopInit(ID3D12Device* dev);
	void PopUpdate();
	void PopTransition();
	void PopDraw(ID3D12GraphicsCommandList* cmdList_, ID3D12Device* dev);
	void PopCollision();

	bool IsDead() { return isDead; }
	void revival() { isDead = false; };
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

