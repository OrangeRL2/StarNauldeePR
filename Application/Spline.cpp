#include "Spline.h"
#include <windows.h>
#include <sysinfoapi.h>

void Spline::Initialize() {
	startCount = GetTickCount64();
}

XMFLOAT3 Spline::Update(std::vector<XMFLOAT3>& points, float timeRate) {

		//�o�ߎ��Ԃ̌v�Z
		nowCount = GetTickCount64();
		elapsedCount = nowCount - startCount;
		float elapsedTime = static_cast<float> (elapsedCount) / 1000.0f;

		timeRate = elapsedTime / maxTime;

		//timeRate��1.0f�ȏ�ɂȂ�����A���̋�Ԃɐi��
		if (timeRate >= 1.0f) {
			if (startIndex < points.size() - 3) {

				startIndex++;

				timeRate -= 1.0f;
				startCount = GetTickCount64();
			}
			else {
				timeRate = 1.0f;
			}
		}

		XMFLOAT3 pos = SplinePosition(points, startIndex, timeRate);

		return pos;
	}


void Spline::Draw() {

}

XMFLOAT3 Spline::SplinePosition(std::vector<XMFLOAT3>& points, size_t startIndex, float t) {
	//��Ԃ��ׂ��_
	size_t n = points.size() - 2;

	if (startIndex > n) return points[n];
	if (startIndex < 1) return points[1];

	//p0~p3�̐���_���擾����
	XMFLOAT3 p0_ = points[startIndex - 1];
	XMFLOAT3 p1_ = points[startIndex];
	XMFLOAT3 p2_ = points[startIndex + 1];
	XMFLOAT3 p3_ = points[startIndex + 2];

	//Catmull-Rom �̎��ɂ����
	XMFLOAT3 position;

	position.x = 0.5f * (p1_.x * 2.0f + (-p0_.x + p2_.x) *
		t + (p0_.x * 2 - p1_.x * 5 + p2_.x * 4 - p3_.x) *
		(t * t) + (-p0_.x + p1_.x * 3 - p2_.x * 3 + p3_.x) *
		(t * t * t));

	position.y = 0.5f * (p1_.y * 2.0f + (-p0_.y + p2_.y) *
		t + (p0_.y * 2 - p1_.y * 5 + p2_.y * 4 - p3_.y) *
		(t * t) + (-p0_.y + p1_.y * 3 - p2_.y * 3 + p3_.y) *
		(t * t * t));

	position.z = 0.5f * (p1_.z * 2.0f + (-p0_.z + p2_.z) *
		t + (p0_.z * 2 - p1_.z * 5 + p2_.z * 4 - p3_.z) *
		(t * t) + (-p0_.z + p1_.z * 3 - p2_.z * 3 + p3_.z) *
		(t * t * t));

	return position;
}