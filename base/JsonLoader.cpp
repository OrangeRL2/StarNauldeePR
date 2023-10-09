#include "JsonLoader.h"
#include "json.hpp"
#include "fstream"
#include "cassert"

#define PI 3.1415f

void JsonLoader::LoadFile(const std::string file_name)
{
	objectData.clear();

	std::ifstream file;
	file.open(file_name);
	assert(!file.fail());

	nlohmann::json jsonFileList;
	file >> jsonFileList;

	assert(jsonFileList.is_object());
	assert(jsonFileList.contains("name"));
	assert(jsonFileList["name"].is_string());

	std::string name = jsonFileList["name"].get<std::string>();
	assert(name.compare("scene") == 0);

	ObjectData objectData1;

	for (nlohmann::json& object : jsonFileList["objects"]) {
		assert(object.contains("type"));

		std::string type = object["type"].get<std::string>();

		//MESH
		if (type.compare("MESH") == 0) {

			if (object.contains("file_name")) {

				objectData1.filename = object["file_name"];
			}
			if (object.contains("move_points"))
			{
				nlohmann::json& move_points = object["move_points"];

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

			nlohmann::json& transform = object["transform"];

			objectData1.translation.x = (float)transform["translation"][0];
			objectData1.translation.y = (float)transform["translation"][2];
			objectData1.translation.z = -(float)transform["translation"][1];

			objectData1.rotation.x = (float)transform["rotation"][0];
			objectData1.rotation.y = (float)transform["rotation"][2];
			objectData1.rotation.z = (float)transform["rotation"][1];

			objectData1.rotation.x *= 1.0f / 360.0f * (2.0f * PI);
			objectData1.rotation.y *= 1.0f / 360.0f * (2.0f * PI);
			objectData1.rotation.z *= 1.0f / 360.0f * (2.0f * PI);

			objectData1.scaling.x = (float)transform["scaling"][0];
			objectData1.scaling.y = (float)transform["scaling"][2];
			objectData1.scaling.z = (float)transform["scaling"][1];

			// TODO: COLLIDER

			// TODO: Combine object traversal into a recursive function and traverse branches with recursive calls
			/*if (object.contains("children")) {

			}*/

			objectData.push_back(objectData1);
		}
	}
}