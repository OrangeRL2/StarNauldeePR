#include "MathFunc.h"
#include <stdlib.h>

//�C�[�W���O
float MathFunc::easeOutQuint(float number) {
	return 1 - pow(1 - number, 5);
}
float MathFunc::easeInQuint(float number) {
	return number * number * number * number * number;
}
float MathFunc::easeInOutSine(float number) {
	return -(cos(Pie * number) - 1) / 2;
}

//�X�P�[�����O�s���ݒ肷��֐�
void MathFunc::Affine::SetMatScale(XMMATRIX& affineMat, DirectX::XMFLOAT3 scale) {
	//�X�P�[�����O�s���錾
	XMMATRIX matScale = {
		scale.x , 0 , 0 , 0 ,
		0 , scale.y , 0 , 0 ,
		0 , 0 , scale.z , 0 ,
		0 , 0 , 0 , 1 ,
	};

	//�s��̌v�Z
	affineMat *= matScale;

}

//��]�s���ݒ肷��֐�
void MathFunc::Affine::SetMatRotation(XMMATRIX& affineMat, DirectX::XMFLOAT3 rotation) {

	//��]�s���錾
	//Z����]
	XMMATRIX matRotZ = {
		(float)cos(rotation.z) , (float)sin(rotation.z) , 0 , 0 ,
		(float)-sin(rotation.z) , (float)cos(rotation.z) , 0 , 0 ,
		0 , 0 , 1 , 0 ,
		0 , 0 , 0 , 1 ,
	};

	//X����]
	XMMATRIX matRotX = {
		1 , 0 , 0 , 0 ,
		0 , (float)cos(rotation.x) , (float)sin(rotation.x) , 0 ,
		0 , -(float)sin(rotation.x) , (float)cos(rotation.x) , 0 ,
		0 , 0 , 0 , 1 ,
	};

	//Y����]
	XMMATRIX matRotY = {
		(float)cos(rotation.y) , 0 , (float)-sin(rotation.y) , 0 ,
		0 , 1 , 0 , 0 ,
		(float)sin(rotation.y) , 0 , (float)cos(rotation.y) , 0 ,
		0 , 0 , 0 , 1 ,
	};

	//�s��̌v�Z
	affineMat *= matRotX;
	affineMat *= matRotY;
	affineMat *= matRotZ;

}

//���s�ړ��s��̐ݒ������֐�
void MathFunc::Affine::SetMatTranslation(XMMATRIX& affineMat, DirectX::XMFLOAT3 translation) {

	//���s�ړ��s��̐錾
	XMMATRIX matTranslation = {
		1 , 0 , 0 , 0 ,
		0 , 1 , 0 , 0 ,
		0 , 0 , 1 , 0 ,
		translation.x , translation.y , translation.z , 1 ,
	};

	//�s��̌v�Z
	affineMat *= matTranslation;
}
#pragma endregion

#pragma region//���[���h�ϊ��s��𐶐�����֐�
//�X�P�[�����O�s��𐶐�����֐�
XMMATRIX MathFunc::Affine::CreateMatScale(DirectX::XMFLOAT3 scale) {

	//�X�P�[�����O�s���錾
	XMMATRIX matScale = {
		scale.x , 0 , 0 , 0 ,
		0 , scale.y , 0 , 0 ,
		0 , 0 , scale.z , 0 ,
		0 , 0 , 0 , 1 ,
	};

	//�s��̌v�Z
	return matScale;

}

//��]�s��𐶐�����֐�
XMMATRIX MathFunc::Affine::CreateMatRotation(DirectX::XMFLOAT3 rotation) {

	//��]�s���錾
	XMMATRIX matRot;

	//Z����]
	XMMATRIX matRotZ = {
		(float)cos(rotation.z) , (float)sin(rotation.z) , 0 , 0 ,
		(float)-sin(rotation.z) , (float)cos(rotation.z) , 0 , 0 ,
		0 , 0 , 1 , 0 ,
		0 , 0 , 0 , 1 ,
	};

	//X����]
	XMMATRIX matRotX = {
		1 , 0 , 0 , 0 ,
		0 , (float)cos(rotation.x) , (float)sin(rotation.x) , 0 ,
		0 , (float)-sin(rotation.x) , (float)cos(rotation.x) , 0 ,
		0 , 0 , 0 , 1 ,
	};

	//Y����]
	XMMATRIX matRotY = {
		(float)cos(rotation.y) , 0 , (float)-sin(rotation.y) , 0 ,
		0 , 1 , 0 , 0 ,
		(float)sin(rotation.y) , 0 , (float)cos(rotation.y) , 0 ,
		0 , 0 , 0 , 1 ,
	};

	//�s��̌v�Z
	matRot *= matRotZ;
	matRot *= matRotX;
	matRot *= matRotY;

	return matRot;

}


//���s�ړ��s��̐���������֐�
XMMATRIX MathFunc::Affine::CreateMatTranslation(DirectX::XMFLOAT3 translation) {

	//���s�ړ��s��̐錾
	XMMATRIX matTranslation = {
		1 , 0 , 0 , 0 ,
		0 , 1 , 0 , 0 ,
		0 , 0 , 1 , 0 ,
		translation.x , translation.y , translation.z , 1 ,
	};

	//�s��̌v�Z
	return matTranslation;
}

#pragma endregion


//�r���[�s��𐶐�����֐�
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

#pragma region//�x���@�̌ʓx�@�̊֐�

//�x���@���ʓx�@�ɕϊ�����֐�
float MathFunc::Utility::Deg2Rad(float Deg) {

	return Deg * MathFunc::Pie / 180;

}

//�ʓx�@��x���@�ɕϊ�����֐�
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