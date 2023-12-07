#pragma once
#include "Windows.h"
#include "cstdint"

static const int window_width = 1280;	//window width
static const int window_height = 720;	//window height
/**
 * @file WinApp.h
 * @brief Class to create and manage a window
 * @author Nauldee Nawill
 */
class WinApp
{
public:
	//Window Procedure
	static LRESULT WindowProc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam);

public:
	static WinApp* GetInstance();
	//Window Generation
	void CreateWindow_(const wchar_t* title);
	//Window Class Deletion
	void deleteWindow();
	//ゲッター
	HWND GetHwnd() { return hwnd; };
public:
	//Member variables
	WNDCLASSEX w{};
	HWND hwnd;
};
