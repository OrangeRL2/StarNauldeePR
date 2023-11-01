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
	//functions
	void Initialize();

	XMFLOAT3 Update(std::vector<XMFLOAT3>& points, float t);

	void Draw();
	//sets points for the spline
	XMFLOAT3 SplinePosition(std::vector<XMFLOAT3>& point, size_t startIndex, float t);

private:
	//variables
	long long startCount;
	long long nowCount;
	double elapsedCount = 0;

	float maxTime = 5.0f;

	size_t startIndex = 1;

	XMFLOAT3 position;
};