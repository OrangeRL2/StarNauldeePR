#include "MathFunc.h"
#include <stdlib.h>
#pragma warning(disable:4828) 
//イージング
float MathFunc::easeOutQuint(float number) {
	return 1 - pow(1 - number, 5);
}
float MathFunc::easeInQuint(float number) {
	return number * number * number * number * number;
}
float MathFunc::easeInOutSine(float number) {
	return -(cos(Pie * number) - 1) / 2;
}
float MathFunc::DegreeConversionRad(float frequencymethod)
{
	return Pie / 180 * frequencymethod;
}
//スケーリング行列を設定する関数
void MathFunc::Affine::SetMatScale(XMMATRIX& affineMat, DirectX::XMFLOAT3 scale) {
	//スケーリング行列を宣言
	XMMATRIX matScale = {
		scale.x , 0 , 0 , 0 ,
		0 , scale.y , 0 , 0 ,
		0 , 0 , scale.z , 0 ,
		0 , 0 , 0 , 1 ,
	};

	//行列の計算
	affineMat *= matScale;

}

//回転行列を設定する関数
void MathFunc::Affine::SetMatRotation(XMMATRIX& affineMat, DirectX::XMFLOAT3 rotation) {

	//回転行列を宣言
	//Z軸回転
	XMMATRIX matRotZ = {
		(float)cos(rotation.z) , (float)sin(rotation.z) , 0 , 0 ,
		(float)-sin(rotation.z) , (float)cos(rotation.z) , 0 , 0 ,
		0 , 0 , 1 , 0 ,
		0 , 0 , 0 , 1 ,
	};

	//X軸回転
	XMMATRIX matRotX = {
		1 , 0 , 0 , 0 ,
		0 , (float)cos(rotation.x) , (float)sin(rotation.x) , 0 ,
		0 , -(float)sin(rotation.x) , (float)cos(rotation.x) , 0 ,
		0 , 0 , 0 , 1 ,
	};

	//Y軸回転
	XMMATRIX matRotY = {
		(float)cos(rotation.y) , 0 , (float)-sin(rotation.y) , 0 ,
		0 , 1 , 0 , 0 ,
		(float)sin(rotation.y) , 0 , (float)cos(rotation.y) , 0 ,
		0 , 0 , 0 , 1 ,
	};

	//行列の計算
	affineMat *= matRotX;
	affineMat *= matRotY;
	affineMat *= matRotZ;

}

//平行移動行列の設定をする関数
void MathFunc::Affine::SetMatTranslation(XMMATRIX& affineMat, DirectX::XMFLOAT3 translation) {

	//平行移動行列の宣言
	XMMATRIX matTranslation = {
		1 , 0 , 0 , 0 ,
		0 , 1 , 0 , 0 ,
		0 , 0 , 1 , 0 ,
		translation.x , translation.y , translation.z , 1 ,
	};

	//行列の計算
	affineMat *= matTranslation;
}
#pragma endregion

#pragma region//ワールド変換行列を生成する関数
//スケーリング行列を生成する関数
XMMATRIX MathFunc::Affine::CreateMatScale(DirectX::XMFLOAT3 scale) {

	//スケーリング行列を宣言
	XMMATRIX matScale = {
		scale.x , 0 , 0 , 0 ,
		0 , scale.y , 0 , 0 ,
		0 , 0 , scale.z , 0 ,
		0 , 0 , 0 , 1 ,
	};

	//行列の計算
	return matScale;

}

//回転行列を生成する関数
XMMATRIX MathFunc::Affine::CreateMatRotation(DirectX::XMFLOAT3 rotation) {

	//回転行列を宣言
	XMMATRIX matRot;

	//Z軸回転
	XMMATRIX matRotZ = {
		(float)cos(rotation.z) , (float)sin(rotation.z) , 0 , 0 ,
		(float)-sin(rotation.z) , (float)cos(rotation.z) , 0 , 0 ,
		0 , 0 , 1 , 0 ,
		0 , 0 , 0 , 1 ,
	};

	//X軸回転
	XMMATRIX matRotX = {
		1 , 0 , 0 , 0 ,
		0 , (float)cos(rotation.x) , (float)sin(rotation.x) , 0 ,
		0 , (float)-sin(rotation.x) , (float)cos(rotation.x) , 0 ,
		0 , 0 , 0 , 1 ,
	};

	//Y軸回転
	XMMATRIX matRotY = {
		(float)cos(rotation.y) , 0 , (float)-sin(rotation.y) , 0 ,
		0 , 1 , 0 , 0 ,
		(float)sin(rotation.y) , 0 , (float)cos(rotation.y) , 0 ,
		0 , 0 , 0 , 1 ,
	};

	//行列の計算
	matRot *= matRotZ;
	matRot *= matRotX;
	matRot *= matRotY;

	return matRot;

}


//平行移動行列の生成をする関数
XMMATRIX MathFunc::Affine::CreateMatTranslation(DirectX::XMFLOAT3 translation) {

	//平行移動行列の宣言
	XMMATRIX matTranslation = {
		1 , 0 , 0 , 0 ,
		0 , 1 , 0 , 0 ,
		0 , 0 , 1 , 0 ,
		translation.x , translation.y , translation.z , 1 ,
	};

	//行列の計算
	return matTranslation;
}

#pragma endregion


//ビュー行列を生成する関数
XMMATRIX MathFunc::Utility::CreatMatView(DirectX::XMFLOAT3 eye, DirectX::XMFLOAT3 target, DirectX::XMFLOAT3 up) {

	XMMATRIX matView;

	XMFLOAT3 xmEye;
	xmEye.x = eye.x;
	xmEye.y = eye.y;
	xmEye.z = eye.z;

	XMFLOAT3 xmTarget;
	xmTarget.x = target.x;
	xmTarget.y = target.y;
	xmTarget.z = target.z;

	XMFLOAT3 xmUp;
	xmUp.x = up.x;
	xmUp.y = up.y;
	xmUp.z = up.z;

	XMMATRIX xmMatView = XMMatrixLookAtLH(
		XMLoadFloat3(&xmEye), XMLoadFloat3(&xmTarget), XMLoadFloat3(&xmUp));

	//xmMatView *= XMMatrixPerspectiveFovLH(XM_PIDIV4,1280 / 720,1.0f,100.0f);
	xmMatView *= XMMatrixPerspectiveFovLH(2.0f, 1280 / 720, 1.0f, 100.0f);


	return matView;

}

#pragma region//度数法⇔弧度法の関数

//度数法を弧度法に変換する関数
float MathFunc::Utility::Deg2Rad(float Deg) {

	return Deg * MathFunc::Pie / 180;

}

//弧度法を度数法に変換する関数
float MathFunc::Utility::Rad2Deg(float rad) {

	return rad / MathFunc::Pie * 180;

}

#pragma endregion

int MathFunc::RNG(int min, int max, bool preciseMode)
{
	if (!preciseMode) {
		return (rand() % (max + 1 - min) + min);
	}

	int ret = 0;
	do {
		ret = rand();
	} while (ret >= RAND_MAX - RAND_MAX % (max + 1 - min));
	ret = ret % (max + 1 - min) + min;
	return ret;
}
