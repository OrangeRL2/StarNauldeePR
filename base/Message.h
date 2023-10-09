#pragma once
//#include "dxgidebug.h"
#include <d3d12.h>

class Message
{
public:
	static Message* GetInstance();

	bool Update();

	bool CheckError();
public:
	MSG msg{};
};

