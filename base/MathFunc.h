#pragma once
#include <math.h>
#include <DirectXMath.h>
using namespace DirectX;

namespace MathFunc {

	const float Pie = 3.141592f;

	//イージング
	float easeOutQuint(float number);
	float easeInQuint(float number);
	float easeInOutSine(float number);

	namespace Affine {
		//ワールド変換行列を設定する関数
		void SetMatScale(			XMMATRIX& affineMat, DirectX::XMFLOAT3 scale);				//スケーリング行列を設定する関数
		void SetMatRotation(		XMMATRIX& affineMat, DirectX::XMFLOAT3 rotation);			//回転行列を設定する関数
		void SetMatTranslation(		XMMATRIX& affineMat, DirectX::XMFLOAT3 translation);	//平行移動行列の設定をする関数

		//ワールド変換行列を生成する関数
		XMMATRIX CreateMatScale(DirectX::XMFLOAT3 scale);				//スケーリング行列を生成する関数
		XMMATRIX CreateMatRotation(DirectX::XMFLOAT3 rotation);		//回転行列を生成する関数
		XMMATRIX CreateMatTranslation(DirectX::XMFLOAT3 translation);	//平行移動行列の生成をする関数

	}

	namespace Utility {
		//ビュー行列を生成する関数
		XMMATRIX CreatMatView(DirectX::XMFLOAT3 eye, DirectX::XMFLOAT3 target, DirectX::XMFLOAT3 up);

		//度数法⇔弧度法の関数
		float Deg2Rad(float Deg);	//度数法を弧度法に変換する関数
		float Rad2Deg(float rad);	//弧度法を度数法に変換する関数

		//ベクトルと行列の掛け算をする関数
		DirectX::XMFLOAT3 MulVector3AndMatrix4(DirectX::XMFLOAT3 vec, XMMATRIX mat);

	}
	int RNG(int min, int max, bool preciseMode = false);
}