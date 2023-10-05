#include "JsonLoader.h"
#include "json.hpp"
#include "fstream"
#include "cassert"

#define PI 3.1415

void JsonLoader::LoadFile(const std::string file_name)
{
	//オブジェクトデータリセット
	objectData.clear();

	//ファイルを開く
	std::ifstream file;
	file.open(file_name);
	assert(!file.fail());

	//json文字列
	nlohmann::json jsonFileList;
	//json文字列に代入
	file >> jsonFileList;

	//正しいレベルデータファイルかチェック
	assert(jsonFileList.is_object());
	assert(jsonFileList.contains("name"));
	assert(jsonFileList["name"].is_string());

	//"name"を文字列として取得
	std::string name = jsonFileList["name"].get<std::string>();
	assert(name.compare("scene") == 0);

	//オブジェクトデータ格納用インスタンスを生成
	ObjectData objectData1;

	// "objects"の全オブジェクトを走査
	for (nlohmann::json& object : jsonFileList["objects"]) {
		assert(object.contains("type"));

		// 種別を取得
		std::string type = object["type"].get<std::string>();

		//MESH
		if (type.compare("MESH") == 0) {

			if (object.contains("file_name")) {
				// ファイル名
				objectData1.filename = object["file_name"];
			}
			if (object.contains("move_points"))
			{
				nlohmann::json& move_points = object["move_points"];
				//平行移動
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
			// トランスフォームのパラメータ読み込み
			nlohmann::json& transform = object["transform"];
			// 平行移動
			objectData1.translation.x = (float)transform["translation"][0];
			objectData1.translation.y = (float)transform["translation"][2];
			objectData1.translation.z = -(float)transform["translation"][1];
			// 回転角
			objectData1.rotation.x = (float)transform["rotation"][0];
			objectData1.rotation.y = (float)transform["rotation"][2];
			objectData1.rotation.z = (float)transform["rotation"][1];
			//弧度法に変換
			objectData1.rotation.x *= 1.0f / 360.0f * (2.0f * PI);
			objectData1.rotation.y *= 1.0f / 360.0f * (2.0f * PI);
			objectData1.rotation.z *= 1.0f / 360.0f * (2.0f * PI);
			// スケーリング
			objectData1.scaling.x = (float)transform["scaling"][0];
			objectData1.scaling.y = (float)transform["scaling"][2];
			objectData1.scaling.z = (float)transform["scaling"][1];

			// TODO: コライダーのパラメータ読み込み

			// TODO: オブジェクト走査を再帰関数にまとめ、再帰呼出で枝を走査する
			/*if (object.contains("children")) {

			}*/

			//オブジェクトデータに代入
			objectData.push_back(objectData1);
		}
	}
}