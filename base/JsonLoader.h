#pragma once
#include "array"
#include "DirectXMath.h"
#include "vector"
#include "memory"
#include "string"
#include "list"

class JsonLoader
{
private:	//エイリアス
	//DirectX::を省略
	using XMFLOAT2 = DirectX::XMFLOAT2;
	using XMFLOAT3 = DirectX::XMFLOAT3;
	using XMFLOAT4 = DirectX::XMFLOAT4;
	using XMMATRIX = DirectX::XMMATRIX;
	
public:
	struct ObjectData {
		// ファイル名
		std::string filename;
		// 平行移動
		XMFLOAT3 translation;
		// 回転角
		XMFLOAT3 rotation;
		// スケーリング
		XMFLOAT3 scaling;
		//動き
		XMFLOAT3 point_1;
		XMFLOAT3 point_2;
		XMFLOAT3 point_3;
		XMFLOAT3 point_4;
		XMFLOAT3 point_5;
	};

	//メンバ関数
public:
	void LoadFile(const std::string file_name);

	//ゲッター
	size_t GetObjectDatas() { return objectData.size(); }
	ObjectData GetObjectData(int number) { return objectData[number]; }
	std::string GetFileName(int number) { return objectData[number].filename; }
	XMFLOAT3 GetPosition(int number) { return objectData[number].translation; }
	XMFLOAT3 GetRotation(int number) { return objectData[number].rotation; }
	XMFLOAT3 GetScale(int number) { return objectData[number].scaling; }
	XMFLOAT3 GetPoint1(int number) { return objectData[number].point_1; }
	XMFLOAT3 GetPoint2(int number) { return objectData[number].point_2; }
	XMFLOAT3 GetPoint3(int number) { return objectData[number].point_3; }
	XMFLOAT3 GetPoint4(int number) { return objectData[number].point_4; }
	XMFLOAT3 GetPoint5(int number) { return objectData[number].point_5; }

	//メンバ変数
private:
	std::vector<ObjectData>objectData;
};