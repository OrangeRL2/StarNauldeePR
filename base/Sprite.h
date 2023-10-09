#pragma once
#include <Windows.h>
#include <D3dx12.h>

#include <DirectXMath.h>
using namespace DirectX;

#include <d3dcompiler.h>
#pragma comment(lib, "d3dcompiler.lib")

#include <wrl.h>

using namespace Microsoft::WRL;

#include <cassert>

#include <DirectXTex.h>

#include "DirectXCommon.h"

struct PipelineSet {

	ComPtr<ID3D12PipelineState> pipelinestate;

	ComPtr<ID3D12RootSignature> rootsignature;

};


//sprite
struct VertexPosUv {
	XMFLOAT3 pos;
	XMFLOAT2 uv;
};


struct SpriteCommon {

	//Maximum number of textures
	static const int spriteSRVCount = 512;

	
	PipelineSet pipelineSet;


	XMMATRIX matProjection{};

	ComPtr<ID3D12DescriptorHeap> descHeap;

	ComPtr<ID3D12Resource> texBuff[spriteSRVCount];

};

class Sprite
{
	//-----------SPRITE----------

public:


	void SetPiplineSet(PipelineSet piplineSet);

	PipelineSet SpriteCreateGraphicsPipeline(ID3D12Device* dev);


	ComPtr<ID3D12Resource> vertBuff;

	D3D12_VERTEX_BUFFER_VIEW vbView{};

private:

	ComPtr<ID3D12Resource> constBuff;

	float rotation = 0.0f;

	XMFLOAT3 position = { 0,0,0 };

	XMMATRIX matWorld;

	UINT texNumber = 0;

	XMFLOAT2 size = { 100,100 };

	struct ConstBufferData {
		XMFLOAT4 color; 
		XMMATRIX mat; 
	};

	//commandlist
	ComPtr<ID3D12GraphicsCommandList> cmdList;
	DirectXCommon* dx = nullptr;
	ComPtr<ID3D12DescriptorHeap> descHeap;
	D3D12_DESCRIPTOR_HEAP_DESC srvHeapDesc = {};

public:


	void SpriteCreate(ID3D12Device* dev, int window_width, int window_height);


	SpriteCommon SpriteCommonCreate(ID3D12Device* dev, int window_width, int window_height);


	void SpriteCommonBeginDraw(ID3D12GraphicsCommandList* cmdList, const SpriteCommon& spriteCommon);

	void SpriteDraw(ID3D12GraphicsCommandList* cmdList_, const SpriteCommon& spriteCommon, ID3D12Device* dev,
		D3D12_VERTEX_BUFFER_VIEW& vbView);

	void SpriteUpdate(Sprite& sprite, const SpriteCommon& spriteCommon);

	void SpriteCommonLoadTexture(SpriteCommon& spriteCommon, UINT texnumber, const wchar_t* filename, ID3D12Device* dev);

	void SpriteTransferVertexBuffer(const Sprite& sprite);

	void SetTexNumber(UINT texnumber) { this->texNumber = texnumber; }

	void SetPosition(XMFLOAT3 position) { this->position = position; }
	void SetRotation(float rotation) { this->rotation = rotation; }
	void SetScale(XMFLOAT2 scale) { this->size = scale; }


	void Release();
};