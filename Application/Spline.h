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
	//������
	void Initialize();

	//�X�V
	XMFLOAT3 Update(std::vector<XMFLOAT3>& points, float t);

	//�`��
	void Draw();

	//����_�̏W��(vector�R���e�i)�A��Ԃ����Ԃ̓Y���A���Ԍo�ߗ�
	XMFLOAT3 SplinePosition(std::vector<XMFLOAT3>& point, size_t startIndex, float t);

private:
	//���Ԍv�Z�ɕK�v�ȃf�[�^
	long long startCount;
	long long nowCount;
	double elapsedCount = 0;

	float maxTime = 5.0f;				//�S�̎���[s]

	//P1����X�^�[�g����
	size_t startIndex = 1;

	//���̈ʒu
	XMFLOAT3 position;
};