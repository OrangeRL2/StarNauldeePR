#include "FPS.h"

void FPS::FpsControlBegin() {

	QueryPerformanceFrequency(&cpuClock);

	QueryPerformanceCounter(&timeStart);
}

void FPS::FpsControlEnd() {

	QueryPerformanceCounter(&timeEnd);

	float elapsedFrame = static_cast<float>(timeEnd.QuadPart - timeStart.QuadPart) /
		static_cast<float>(cpuClock.QuadPart);

	if (elapsedFrame < frameTime) {

		DWORD sleepTime = static_cast<DWORD>((frameTime - elapsedFrame) * 1000.0f);
		timeBeginPeriod(1);

		Sleep(sleepTime);
		timeEndPeriod(1);
	}

	fps = 1 / elapsedFrame;
}

void FPS::SetFrameRate(float fps_) { frameTime = 1.0f / fps_; }

float FPS::GetFrameRate() { return fps; }