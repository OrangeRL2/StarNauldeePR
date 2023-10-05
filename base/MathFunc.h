#pragma once
#include <math.h>
#include <DirectXMath.h>
using namespace DirectX;

namespace MathFunc {

	const float Pie = 3.141592f;

	//�C�[�W���O
	float easeOutQuint(float number);
	float easeInQuint(float number);
	float easeInOutSine(float number);

	namespace Affine {
		//���[���h�ϊ��s���ݒ肷��֐�
		void SetMatScale(			XMMATRIX& affineMat, DirectX::XMFLOAT3 scale);				//�X�P�[�����O�s���ݒ肷��֐�
		void SetMatRotation(		XMMATRIX& affineMat, DirectX::XMFLOAT3 rotation);			//��]�s���ݒ肷��֐�
		void SetMatTranslation(		XMMATRIX& affineMat, DirectX::XMFLOAT3 translation);	//���s�ړ��s��̐ݒ������֐�

		//���[���h�ϊ��s��𐶐�����֐�
		XMMATRIX CreateMatScale(DirectX::XMFLOAT3 scale);				//�X�P�[�����O�s��𐶐�����֐�
		XMMATRIX CreateMatRotation(DirectX::XMFLOAT3 rotation);		//��]�s��𐶐�����֐�
		XMMATRIX CreateMatTranslation(DirectX::XMFLOAT3 translation);	//���s�ړ��s��̐���������֐�

	}

	namespace Utility {
		//�r���[�s��𐶐�����֐�
		XMMATRIX CreatMatView(DirectX::XMFLOAT3 eye, DirectX::XMFLOAT3 target, DirectX::XMFLOAT3 up);

		//�x���@�̌ʓx�@�̊֐�
		float Deg2Rad(float Deg);	//�x���@���ʓx�@�ɕϊ�����֐�
		float Rad2Deg(float rad);	//�ʓx�@��x���@�ɕϊ�����֐�

		//�x�N�g���ƍs��̊|���Z������֐�
		DirectX::XMFLOAT3 MulVector3AndMatrix4(DirectX::XMFLOAT3 vec, XMMATRIX mat);

	}
	int RNG(int min, int max, bool preciseMode = false);
}