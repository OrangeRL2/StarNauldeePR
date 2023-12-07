#pragma once
#include <fstream>
#include <sstream>
#include <windows.h>
#include <timeapi.h>
#pragma comment(lib, "winmm.lib")

/**
 * @file FPS.h
 * @brief Class for locking FPS
 * @author Nauldee Nawill
 */

class FPS {
private:
	// CPU frequency
	LARGE_INTEGER cpuClock{};
	//start time
	LARGE_INTEGER timeStart{};
	//end time
	LARGE_INTEGER timeEnd{};

	float frameTime = 1 / 60.0f;
	// FPS値
	float fps;

public:

	void FpsControlBegin();

	void FpsControlEnd();

	void SetFrameRate(float fps_);

	float GetFrameRate();
};

