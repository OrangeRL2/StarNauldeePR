#pragma once
#include "Camera.h"
#include "Input.h"
#include "DXInput.h"
#include "FbxModel.h"
#include "FbxObject3D.h"
#include <Vector>

class Spline
{
public:
	//初期化
	void Initialize();

	//更新
	XMFLOAT3 Update(std::vector<XMFLOAT3>& points, float t);

	//描画
	void Draw();

	//制御点の集合(vectorコンテナ)、補間する区間の添字、時間経過率
	XMFLOAT3 SplinePosition(std::vector<XMFLOAT3>& point, size_t startIndex, float t);

private:
	//時間計算に必要なデータ
	long long startCount;
	long long nowCount;
	double elapsedCount = 0;

	float maxTime = 5.0f;				//全体時間[s]

	//P1からスタートする
	size_t startIndex = 1;

	//球の位置
	XMFLOAT3 position;
};