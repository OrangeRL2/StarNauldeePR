#include "JsonLoader.h"
#include "json.hpp"
#include "fstream"
#include "cassert"

#define PI 3.1415

void JsonLoader::LoadFile(const std::string file_name)
{
	//�I�u�W�F�N�g�f�[�^���Z�b�g
	objectData.clear();

	//�t�@�C�����J��
	std::ifstream file;
	file.open(file_name);
	assert(!file.fail());

	//json������
	nlohmann::json jsonFileList;
	//json������ɑ��
	file >> jsonFileList;

	//���������x���f�[�^�t�@�C�����`�F�b�N
	assert(jsonFileList.is_object());
	assert(jsonFileList.contains("name"));
	assert(jsonFileList["name"].is_string());

	//"name"�𕶎���Ƃ��Ď擾
	std::string name = jsonFileList["name"].get<std::string>();
	assert(name.compare("scene") == 0);

	//�I�u�W�F�N�g�f�[�^�i�[�p�C���X�^���X�𐶐�
	ObjectData objectData1;

	// "objects"�̑S�I�u�W�F�N�g�𑖍�
	for (nlohmann::json& object : jsonFileList["objects"]) {
		assert(object.contains("type"));

		// ��ʂ��擾
		std::string type = object["type"].get<std::string>();

		//MESH
		if (type.compare("MESH") == 0) {

			if (object.contains("file_name")) {
				// �t�@�C����
				objectData1.filename = object["file_name"];
			}
			if (object.contains("move_points"))
			{
				nlohmann::json& move_points = object["move_points"];
				//���s�ړ�
				objectData1.point_1.x = (float)move_points["point_1"][0];
				objectData1.point_1.y = (float)move_points["point_1"][2];
				objectData1.point_1.z = -(float)move_points["point_1"][1];

				objectData1.point_2.x = (float)move_points["point_2"][0];
				objectData1.point_2.y = (float)move_points["point_2"][2];
				objectData1.point_2.z = -(float)move_points["point_2"][1];

				objectData1.point_3.x = (float)move_points["point_3"][0];
				objectData1.point_3.y = (float)move_points["point_3"][2];
				objectData1.point_3.z = -(float)move_points["point_3"][1];

				objectData1.point_4.x = (float)move_points["point_4"][0];
				objectData1.point_4.y = (float)move_points["point_4"][2];
				objectData1.point_4.z = -(float)move_points["point_4"][1];

				objectData1.point_5.x = (float)move_points["point_5"][0];
				objectData1.point_5.y = (float)move_points["point_5"][2];
				objectData1.point_5.z = -(float)move_points["point_5"][1];
			}
			// �g�����X�t�H�[���̃p�����[�^�ǂݍ���
			nlohmann::json& transform = object["transform"];
			// ���s�ړ�
			objectData1.translation.x = (float)transform["translation"][0];
			objectData1.translation.y = (float)transform["translation"][2];
			objectData1.translation.z = -(float)transform["translation"][1];
			// ��]�p
			objectData1.rotation.x = (float)transform["rotation"][0];
			objectData1.rotation.y = (float)transform["rotation"][2];
			objectData1.rotation.z = (float)transform["rotation"][1];
			//�ʓx�@�ɕϊ�
			objectData1.rotation.x *= 1.0f / 360.0f * (2.0f * PI);
			objectData1.rotation.y *= 1.0f / 360.0f * (2.0f * PI);
			objectData1.rotation.z *= 1.0f / 360.0f * (2.0f * PI);
			// �X�P�[�����O
			objectData1.scaling.x = (float)transform["scaling"][0];
			objectData1.scaling.y = (float)transform["scaling"][2];
			objectData1.scaling.z = (float)transform["scaling"][1];

			// TODO: �R���C�_�[�̃p�����[�^�ǂݍ���

			// TODO: �I�u�W�F�N�g�������ċA�֐��ɂ܂Ƃ߁A�ċA�ďo�Ŏ}�𑖍�����
			/*if (object.contains("children")) {

			}*/

			//�I�u�W�F�N�g�f�[�^�ɑ��
			objectData.push_back(objectData1);
		}
	}
}