#pragma once
#include "array"
#include "DirectXMath.h"
#include "vector"
#include "memory"
#include "string"
#include "list"

class JsonLoader
{
private:	//�G�C���A�X
	//DirectX::���ȗ�
	using XMFLOAT2 = DirectX::XMFLOAT2;
	using XMFLOAT3 = DirectX::XMFLOAT3;
	using XMFLOAT4 = DirectX::XMFLOAT4;
	using XMMATRIX = DirectX::XMMATRIX;
	
public:
	struct ObjectData {
		// �t�@�C����
		std::string filename;
		// ���s�ړ�
		XMFLOAT3 translation;
		// ��]�p
		XMFLOAT3 rotation;
		// �X�P�[�����O
		XMFLOAT3 scaling;
		//����
		XMFLOAT3 point_1;
		XMFLOAT3 point_2;
		XMFLOAT3 point_3;
		XMFLOAT3 point_4;
		XMFLOAT3 point_5;
	};

	//�����o�֐�
public:
	void LoadFile(const std::string file_name);

	//�Q�b�^�[
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

	//�����o�ϐ�
private:
	std::vector<ObjectData>objectData;
};