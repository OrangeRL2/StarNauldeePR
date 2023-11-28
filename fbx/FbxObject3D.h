#pragma once

#include "FbxModel.h"
#include "Camera.h"

#include "windows.h"
#include "wrl.h"
#include "d3d12.h"
#include "d3dx12.h"
#include "DirectXMath.h"
#include "string.h"

class FbxObject3D
{
private:	//alias
	//Microsoft::WRL::を省略
	template<class T>using ComPtr = Microsoft::WRL::ComPtr<T>;
	//DirectX::omission
	using XMFLOAT2 = DirectX::XMFLOAT2;
	using XMFLOAT3 = DirectX::XMFLOAT3;
	using XMFLOAT4 = DirectX::XMFLOAT4;
	using XMMATRIX = DirectX::XMMATRIX;

public:
	//constant variables
	static const int MAX_BONES = 32;
	//SubClass
	//Constant buffer data structure
	struct ConstBufferDataTransform
	{
		XMMATRIX viewproj;
		XMMATRIX world;
		XMFLOAT3 cameraPos;
	};
	//Constant buffer data structure (skinning)
	struct ConstBufferDataSkin
	{
		XMMATRIX bones[MAX_BONES];
	};

public:	//static member function
	//setter
	static void SetDevice(ID3D12Device* device) { FbxObject3D::device = device; }
	static void SetCamera(Camera* camera) { FbxObject3D::camera = camera; }

private://static member variables
	static ID3D12Device* device;
	static Camera* camera;

public://member functions
	
	void Initialize();
	
	void Update();
	
	void Draw(ID3D12GraphicsCommandList* cmdList);
	//setting model
	void SetModel(FbxModel* model) { this->model = model; }
	//Pipeline Generation
	static void CreateGraphicsPipeline();
	
	void PlayAnimation();

	//Setter
	void SetPosition(XMFLOAT3 pos) { position = pos; }
	void SetRotation(XMFLOAT3 rot) { rotation = rot; }
	void SetScale(XMFLOAT3 sca) { scale = sca; }
	bool SetDeath() { return isDead = true; }
	bool GetDeath() { return isDead; }
	XMFLOAT3 GetPosition() { return position; }
private://member variables
	//constant buffer
	ComPtr<ID3D12Resource>constBuffTransform;
	//Root Signature
	static ComPtr<ID3D12RootSignature>rootsignature;
	//pipeline state object
	static ComPtr<ID3D12PipelineState>pipelinestate;

private:
	//local scale
	XMFLOAT3 scale = { 1,1,1 };
	//local XYZ rotation
	XMFLOAT3 rotation = { 0,0,0 };
	//local position
	XMFLOAT3 position = { 0,0,0 };
	//local matrix
	XMMATRIX matWorld;
	//model
	FbxModel* model = nullptr;

	//constant buffer
	ComPtr<ID3D12Resource>constBuffSkin;

	//1 frame time
	FbxTime frameTime;
	//start frame
	FbxTime startTime;
	//end frame
	FbxTime endTime;
	//current frame
	FbxTime currentTime;
	
	bool isPlay = false;

	//Death
	bool isDead = false;
};