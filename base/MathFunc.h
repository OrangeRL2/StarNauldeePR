#pragma once
#include <math.h>
#include <DirectXMath.h>
using namespace DirectX;

namespace MathFunc {

	const float Pie = 3.141592f;
	float DegreeConversionRad(float frequencymethod);
	float easeOutQuint(float number);
	float easeInQuint(float number);
	float easeInOutSine(float number);

	namespace Affine {

		void SetMatScale(			XMMATRIX& affineMat, DirectX::XMFLOAT3 scale);
		void SetMatRotation(		XMMATRIX& affineMat, DirectX::XMFLOAT3 rotation);
		void SetMatTranslation(		XMMATRIX& affineMat, DirectX::XMFLOAT3 translation);

		XMMATRIX CreateMatScale(DirectX::XMFLOAT3 scale);
		XMMATRIX CreateMatRotation(DirectX::XMFLOAT3 rotation);
		XMMATRIX CreateMatTranslation(DirectX::XMFLOAT3 translation);
	}

	namespace Utility {
		XMMATRIX CreatMatView(DirectX::XMFLOAT3 eye, DirectX::XMFLOAT3 target, DirectX::XMFLOAT3 up);

		float Deg2Rad(float Deg);
		float Rad2Deg(float rad);

		DirectX::XMFLOAT3 MulVector3AndMatrix4(DirectX::XMFLOAT3 vec, XMMATRIX mat);

	}
	int RNG(int min, int max, bool preciseMode = false);
}