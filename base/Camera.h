#pragma once
#include "DirectXMath.h"
#include "Input.h"
#include "DXInput.h"
#include "WinApp.h"
#include <SimpleMath.h>

/**
 * @file Camera.h
 * @brief Class for Camera
 * @author Nauldee Nawill
 */

#define PI 3.14159265359

using namespace DirectX;

class Camera
{

public:
	//singleton instance
	static Camera* GetInstance();
	static void SetInput(Input* input) { Camera::input = input; }
	static void SetDXInput(DXInput* dxInput) { Camera::dxInput = dxInput; }
	//Instructor Destructor
	Camera();
	~Camera();

	void Initialize();
	//更新
	void Update();
	//Arrow key to change viewpoint coordinates
	void DebugUpdate();

	//Getter Setter
	void SetTarget(XMFLOAT3 pos);
	void SetEye(XMFLOAT3 pos);
	XMFLOAT3 GetEye() { return eye_; };
	XMFLOAT3 GetTraget() { return target_; };
	XMFLOAT3 GetUp() { return up_; };
	XMMATRIX GetMatProjection() { return matProjection_; };
	XMMATRIX GetMatView() { return matView_; };
	XMMATRIX GetMatViewProjection() { return matView_ * matProjection_; };

private:
	
	static Input* input;
	//Controller
	static DXInput* dxInput;

	XMMATRIX matProjection_{};

	XMMATRIX matView_{};
	XMFLOAT3 eye_ = { 0, 20, -100 };
	XMFLOAT3 target_ = { 0, 0, 0 };
	XMFLOAT3 up_ = { 0, 1, 0 };

	//Distance to target
	float DebugTargetDistance = 20.0f;
	//加算用
	float DebugChangeRot = 0.0f;
	float DebugChangeRot2 = 0.5f;
	float DebugChangeDistance = 0.0f;
};
