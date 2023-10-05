#include "Camera.h"
#include "Math.h"
#define PI 3.14159265359

Input* Camera::input = nullptr;
DXInput* Camera::dxInput = nullptr;

Camera* Camera::GetInstance()
{
	static Camera instance;
	return &instance;
}

Camera::Camera()
{
	matView_ = XMMatrixLookAtLH(XMLoadFloat3(&eye_), XMLoadFloat3(&target_), XMLoadFloat3(&up_));
}

Camera::~Camera()
{
}

void Camera::Initialize()
{
	//�ˉe�ϊ�
	matProjection_ = XMMatrixPerspectiveFovLH(
		XMConvertToRadians(45.0f),			//�㉺��p45�x
		(float)window_width / window_height,//�A�X�y�N�g��(��ʉ���/��ʗ���)
		0.1f, 1000.0f						//�O�[�A���[
	);

	//�s��v�Z
	matView_ = XMMatrixLookAtLH(XMLoadFloat3(&eye_), XMLoadFloat3(&target_), XMLoadFloat3(&up_));
}


void Camera::Update()
{
	matView_ = XMMatrixLookAtLH(XMLoadFloat3(&eye_), XMLoadFloat3(&target_), XMLoadFloat3(&up_));
}

void Camera::DebugUpdate()
{
	//1�t���[��������̈ړ���
	float rot = (float)PI / 120.0f;

	//���_���W��ύX
	if (input->PushKey(DIK_LEFT))
	{
		DebugChangeRot -= rot;
	}
	if (input->PushKey(DIK_RIGHT))
	{
		DebugChangeRot += rot;
	}
	if (input->PushKey(DIK_UP))
	{
		DebugChangeRot2 -= rot;
	}
	if (input->PushKey(DIK_DOWN))
	{
		DebugChangeRot2 += rot;
	}

	//�^�[�Q�b�g�܂ł̋�����ύX
	if (input->PushKey(DIK_O))
	{
		DebugTargetDistance -= 0.2;
	}
	if (input->PushKey(DIK_P))
	{
		DebugTargetDistance += 0.2;
	}

	//���_���W�ɑ��
	eye_.x = cos(DebugChangeRot) * DebugTargetDistance + target_.x;
	eye_.y = sin(DebugChangeRot2) * DebugTargetDistance + target_.y;
	eye_.z = sin(DebugChangeRot) * DebugTargetDistance + target_.z;
}

void Camera::SetTarget(XMFLOAT3 pos)
{
	target_ = pos;
}

void Camera::SetEye(XMFLOAT3 pos)
{
	eye_ = pos;
}