#pragma once
#include "WinApp.h"
#include "DirectXCommon.h"

/**
 * @file ImGuiManager.h
 * @brief Class for managing IMGui
 * @author Nauldee Nawill
 */

class ImGuiManager
{
public:

	void Initialize(WinApp* winApp, DirectXCommon* dxCommon);

	void Finalize();

	void Begin();

	void End();

	void Draw();


private:
	WinApp* winApp_;
	DirectXCommon* dxCommon_;

	Microsoft::WRL::ComPtr<ID3D12DescriptorHeap>srvHeap_;
};

