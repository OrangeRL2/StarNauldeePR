#pragma once
#include "string"
#include "vector"
#include "DirectXMath.h"
#include "DirectXTex.h"
#include "windows.h"
#include "wrl.h"
#include "d3d12.h"
#include "d3dx12.h"
#include "fbxsdk.h"

struct Node
{
	std::string name;

	DirectX::XMVECTOR scaling = { 1,1,1,0 };

	DirectX::XMVECTOR rotation = { 0,0,0,0 };

	DirectX::XMVECTOR translation = { 0,0,0,1 };

	DirectX::XMMATRIX transform;

	DirectX::XMMATRIX globalTransform;

	Node* parent = nullptr;
};

class FbxModel
{
public:
	//constant 
	//Maximum number of bone indexes
	static const int MAX_BONE_INDICES = 4;
	//friend class
	friend class FbxLoader;
	//subclass
	struct VertexPosNormalUvSkin
	{
		DirectX::XMFLOAT3 pos;
		DirectX::XMFLOAT3 normal;	//normal vector
		DirectX::XMFLOAT2 uv;	//uv coords
		UINT boneIndex[MAX_BONE_INDICES];
		float boneWeight[MAX_BONE_INDICES];
	};
	//Bone Structure
	struct Bone
	{

		std::string name;
		//Inverse matrix of initial pose
		DirectX::XMMATRIX invInitialPose;
		
		FbxCluster* fbxCluster;
		//Constructor
		Bone(const std::string& name)
		{
			this->name = name;
		}
	};

	//Node with mesh
	Node* meshNode = nullptr;
	//vertex data array
	std::vector<VertexPosNormalUvSkin>vertices;
	//vertex index array
	std::vector<unsigned short>indices;

private:

	std::string name;

	std::vector<Node> nodes;

	DirectX::XMFLOAT3 ambient = { 1,1,1 };

	DirectX::XMFLOAT3 diffuse = { 1,1,1 };

	DirectX::TexMetadata metadata = {};

	DirectX::ScratchImage scratchImg = {};

private:	//Alias

	template<class T>using ComPtr = Microsoft::WRL::ComPtr<T>;

	using XMFLOAT2 = DirectX::XMFLOAT2;
	using XMFLOAT3 = DirectX::XMFLOAT3;
	using XMFLOAT4 = DirectX::XMFLOAT4;
	using XMMATRIX = DirectX::XMMATRIX;
	using TexMetadata = DirectX::TexMetadata;
	using ScracthImage = DirectX::ScratchImage;

	using string = std::string;
	template<class T>using vector = std::vector<T>;

private:

	ComPtr<ID3D12Resource> vertBuff;

	ComPtr<ID3D12Resource>indexBuff;

	ComPtr<ID3D12Resource>texBuff;

	D3D12_VERTEX_BUFFER_VIEW vbView = {};

	D3D12_INDEX_BUFFER_VIEW ibView = {};

	ComPtr<ID3D12DescriptorHeap>descHeapSRV;

public:
	//Constructor
	FbxModel() {};
	//Destructor
	~FbxModel();
	//Buffer Generation
	void CreateBuffers(ID3D12Device* device);
	//Drawing
	void Draw(ID3D12GraphicsCommandList* cmdList);
	//Getter for model matrix
	const XMMATRIX& GetModelTransform() { return meshNode->globalTransform; }

private:
	//bone array
	std::vector<Bone>bones;
public:
	//getter
	std::vector<Bone>& GetBones() { return bones; }

private:
	FbxScene* fbxScene = nullptr;
public:
	//getter
	FbxScene* GetFbxScene() { return fbxScene; }
	std::string GetFileName() { return name; }
};

